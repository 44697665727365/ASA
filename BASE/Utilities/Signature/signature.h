#pragma once
#include <cstdint>
#include <string>
#include <vector>

std::uintptr_t get_current_image_base();
std::uint8_t* find_sig(std::uintptr_t image_base, const std::string& byte_array);

class signature
{
public:
    signature(const std::string& sig, std::uintptr_t image_base = get_current_image_base());

    signature instruction(uint32_t offset);
    signature add(uint32_t offset);
    signature sub(uint32_t offset);

#ifdef _WIN64
    uint64_t GetPointer();
#else
    uint32_t GetPointer();
#endif

private:
#ifdef _WIN64
    uint64_t pointer;
#else
    uint32_t pointer;
#endif

    std::string sig;
    std::uintptr_t image_base;
};