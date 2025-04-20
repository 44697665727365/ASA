#pragma once

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;

namespace FreeCRT
{
	namespace Math {
		double Sqrt(double X);
		float PowF(float Base, float Exponent);
		double Pow(double Base, int Exponent);
		bool IsFinite(float Value);
		template<typename T>
		constexpr T Max(const T& A, const T& B)
		{
			return (A > B) ? A : B;
		}
		float AbsF(float X);
		float FmodF(float X, float Y);
	} // namespace Math

	namespace String {
		size_t Strlen(const char* Str);
		size_t Wcslen(const wchar_t* WStr);
		char* StrCpy(char* Dest, const char* Src);
		wchar_t* WcsCpy(wchar_t* Dest, const wchar_t* Src);
		int StrCmp(const char* Str1, const char* Str2);
		int WcsCmp(const wchar_t* WStr1, const wchar_t* WStr2);
		unsigned long Strtoul(const char* Str, char** EndPtr = nullptr, int Base = 10);
	} // namespace String

	namespace Memory {
		void* MemMove(void* Dest, const void* Src, size_t Count);
		void* MemCpy(void* Dest, const void* Src, size_t Count);
		void* MemSet(void* Dest, int Value, size_t Count);
	} // namespace Memory

	namespace TypeTraits {
		template <typename T>
		T&& Declval() noexcept;

		template<typename T> struct RemoveReference { using Type = T; };
		template<typename T> struct RemoveReference<T&> { using Type = T; };
		template<typename T> struct RemoveReference<T&&> { using Type = T; };
		template <typename T>
		constexpr typename RemoveReference<T>::Type&& Move(T&& Obj) noexcept {
			return static_cast<typename RemoveReference<T>::Type&&>(Obj);
		}

		template<typename T>
		T Clamp(T Value, T Min, T Max)
		{
			if (Value < Min) return Min;
			if (Value > Max) return Max;
			return Value;
		}
	} // namespace TypeTraits
}

namespace FMemory
{
	inline void* (*EngineRealloc)(void* Block, uint64 NewSize, uint32 Alignment) = nullptr;

	inline int32 AllocCount = 0x0;

	[[nodiscard]] inline void Init(void* ReallocAddress)
	{
		EngineRealloc = reinterpret_cast<decltype(EngineRealloc)>(ReallocAddress);
	}

	[[nodiscard]] inline void* Malloc(uint64 Size, uint32 Alignment = 0x0 /* auto */)
	{
		return EngineRealloc(nullptr, Size, Alignment);
	}

	[[nodiscard]] inline void* Realloc(void* Ptr, uint64 Size, uint32 Alignment = 0x0 /* auto */)
	{
		return EngineRealloc(Ptr, Size, Alignment);
	}

	inline void Free(void* Ptr)
	{
		EngineRealloc(Ptr, 0x0, 0x0);
	}
}