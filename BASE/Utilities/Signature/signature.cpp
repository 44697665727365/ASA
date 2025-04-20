#include "pch.h"
#include "signature.h"

typedef struct _PEB
{
    BYTE Reserved1[2];
    BYTE BeingDebugged;
    BYTE Reserved2[1];
    PVOID Reserved3[2];
    PVOID ImageBaseAddress;
} PEB;

std::uintptr_t get_current_image_base()
{
#ifdef _WIN64
    PEB* peb = reinterpret_cast<PEB*>(__readgsqword(0x60));
    return reinterpret_cast<std::uintptr_t>(peb->Reserved3[1]);
#else
    PEB* peb = reinterpret_cast<PEB*>(__readfsdword(0x30));
    return reinterpret_cast<std::uintptr_t>(peb->Reserved3[1]);
#endif
}

std::uint8_t* find_sig(std::uintptr_t image_base, const std::string& byte_array)
{
    if (!image_base)
        return nullptr;

    static const auto pattern_to_byte = [](const char* pattern)
        {
            auto bytes = std::vector<int>{};
            const auto start = const_cast<char*>(pattern);
            const auto end = const_cast<char*>(pattern) + FreeCRT::String::Strlen(pattern);

            for (auto current = start; current < end; ++current)
            {
                if (*current == '?')
                {
                    ++current;

                    if (*current == '?')
                        ++current;

                    bytes.push_back(-1);
                }
                else
                {
                    bytes.push_back(FreeCRT::String::Strtoul(current, &current, 16));
                }
            }
            return bytes;
        };

    const auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(image_base);
    const auto nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(image_base + dos_header->e_lfanew);

    const auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
    const auto pattern_bytes = pattern_to_byte(byte_array.c_str());
    const auto scan_bytes = reinterpret_cast<std::uint8_t*>(image_base);

    const auto pattern_size = pattern_bytes.size();
    const auto pattern_data = pattern_bytes.data();

    for (auto i = 0ul; i < size_of_image - pattern_size; ++i)
    {
        auto found = true;

        for (auto j = 0ul; j < pattern_size; ++j)
        {
            if (scan_bytes[i + j] == pattern_data[j] || pattern_data[j] == -1)
                continue;
            found = false;
            break;
        }
        if (!found)
            continue;
        return &scan_bytes[i];
    }

    return nullptr;
}

signature::signature(const std::string& sig, std::uintptr_t image_base) : sig(sig), image_base(image_base)
{
    this->pointer = reinterpret_cast<uint64_t>(find_sig(image_base, sig));
}

signature signature::instruction(uint32_t offset)
{
    this->pointer = *reinterpret_cast<int*>(this->pointer + offset) + this->pointer;
    return *this;
}

signature signature::add(uint32_t offset)
{
    this->pointer += offset;
    return *this;
}

signature signature::sub(uint32_t offset)
{
    this->pointer -= offset;
    return *this;
}

#ifdef _WIN64
uint64_t signature::GetPointer()
{
    return this->pointer;
}
#else
uint32_t signature::GetPointer()
{
    return this->pointer;
}
#endif
