#include "pch.h"
#include "FreeCRT.h"

namespace FreeCRT
{
	namespace Math {
		double Sqrt(double X)
		{
			if (X <= 0) return 0;

			uint64_t I;
			double X2, Y;
			constexpr double ThreeHalfs = 1.5;

			X2 = X * 0.5;
			Y = X;

			Memory::MemCpy(&I, &Y, sizeof(Y));
			I = 0x5FE6EC85E7DE30DA - (I >> 1);
			Memory::MemCpy(&Y, &I, sizeof(Y));

			Y = Y * (ThreeHalfs - (X2 * Y * Y));

			return X * Y;
		}

		float PowF(float Base, float Exponent)
		{
			if (Base == 0.0f) return 0.0f;
			if (Exponent == 0.0f) return 1.0f;
			if (Base < 0.0f) return 0.0f;

			union { float F; int32_t I; } U = { Base };
			float X = (float)(U.I);
			float Log2 = (X * 1.1920928955078125e-7f) - 127.0f; // 1 / (1 << 23)

			float Result = Exponent * Log2;
			float Res_I = (Result + 127.0f) * 8388608.0f; // 1 << 23

			union { int32_t I; float F; } Out = { (int32_t)Res_I };
			return Out.F;
		}

		double Pow(double Base, int Exponent)
		{
			double Result = 1.0;
			while (Exponent != 0) {
				if (Exponent % 2 == 1) Result *= Base;
				Base *= Base;
				Exponent /= 2;
			}
			return Result;
		}

		bool IsFinite(float Value)
		{
			union { float F; uint32_t I; } U = { Value };
			return (U.I & 0x7F800000) != 0x7F800000;
		}

		float AbsF(float X)
		{
			union { float F; uint32_t I; } U = { X };
			U.I &= 0x7FFFFFFF;
			return U.F;
		}

		float FmodF(float X, float Y)
		{
			if (Y == 0.0f)
				return 0.0f;

			int Quotient = static_cast<int>(X / Y);
			return X - (Quotient * Y);
		}

	} // namespace Math

	namespace String {
		size_t Strlen(const char* Str)
		{
			if (!Str)
				return 0;

			size_t Length = 0;
			while (*Str++)
				++Length;

			return Length;
		}

		size_t Wcslen(const wchar_t* WStr)
		{
			if (!WStr)
				return 0;

			size_t Length = 0;
			while (*WStr++)
				++Length;

			return Length;
		}

		char* StrCpy(char* Dest, const char* Src)
		{
			if (!Dest || !Src)
				return Dest;

			char* destPtr = Dest;
			while ((*destPtr++ = *Src++) != '\0');

			return Dest;
		}

		wchar_t* WcsCpy(wchar_t* Dest, const wchar_t* Src)
		{
			if (!Dest || !Src)
				return Dest;

			wchar_t* destPtr = Dest;
			while ((*destPtr++ = *Src++) != L'\0');

			return Dest;
		}

		int StrCmp(const char* Str1, const char* Str2)
		{
			if (!Str1 || !Str2)
				return Str1 ? 1 : (Str2 ? -1 : 0);

			while (*Str1 && (*Str1 == *Str2))
			{
				Str1++;
				Str2++;
			}

			return *(unsigned char*)Str1 - *(unsigned char*)Str2;
		}

		int WcsCmp(const wchar_t* WStr1, const wchar_t* WStr2)
		{
			if (!WStr1 || !WStr2)
				return WStr1 ? 1 : (WStr2 ? -1 : 0);

			while (*WStr1 && (*WStr1 == *WStr2))
			{
				WStr1++;
				WStr2++;
			}

			return *WStr1 - *WStr2;
		}

		unsigned long Strtoul(const char* Str, char** EndPtr, int Base)
		{
			const char* p = Str;
			unsigned long result = 0;
			bool any = false;

			// Skip whitespace (manually, no isspace)
			while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r' || *p == '\f' || *p == '\v')
				++p;

			// Optional '+' or '-' (we ignore negative for unsigned)
			if (*p == '+') {
				++p;
			}
			else if (*p == '-') {
				++p; // Ignored, strtoul handles this as wrap, but we skip here
			}

			// Base auto-detection
			if ((Base == 0 || Base == 16) && p[0] == '0' && (p[1] == 'x' || p[1] == 'X')) {
				Base = 16;
				p += 2;
			}
			else if (Base == 0 && p[0] == '0') {
				Base = 8;
				++p;
			}
			else if (Base == 0) {
				Base = 10;
			}

			// Conversion loop
			while (*p) {
				unsigned char c = *p;
				unsigned long digit;

				if (c >= '0' && c <= '9') {
					digit = c - '0';
				}
				else if (c >= 'a' && c <= 'z') {
					digit = 10 + (c - 'a');
				}
				else if (c >= 'A' && c <= 'Z') {
					digit = 10 + (c - 'A');
				}
				else {
					break;
				}

				if (digit >= (unsigned)Base)
					break;

				result = result * Base + digit;
				++p;
				any = true;
			}

			if (EndPtr)
				*EndPtr = (char*)(any ? p : Str);

			return result;
		}
	} // namespace String

	namespace Memory {
		void* MemMove(void* Dest, const void* Src, size_t Count)
		{
			if (!Dest || !Src || Count == 0)
				return Dest;

			unsigned char* destPtr = static_cast<unsigned char*>(Dest);
			const unsigned char* srcPtr = static_cast<const unsigned char*>(Src);

			if (destPtr < srcPtr)
			{
				for (size_t i = 0; i < Count; ++i)
					destPtr[i] = srcPtr[i];
			}
			else
			{
				for (size_t i = Count; i > 0; --i)
					destPtr[i - 1] = srcPtr[i - 1];
			}

			return Dest;
		}

		void* MemCpy(void* Dest, const void* Src, size_t Count)
		{
			if (!Dest || !Src || Count == 0)
				return Dest;

			uint8* destPtr = static_cast<uint8*>(Dest);
			const uint8* srcPtr = static_cast<const uint8*>(Src);

			for (size_t i = 0; i < Count; ++i)
			{
				destPtr[i] = srcPtr[i];
			}

			return Dest;
		}

		void* MemSet(void* Dest, int Value, size_t Count)
		{
			if (!Dest || Count == 0)
				return Dest;

			uint8* destPtr = static_cast<uint8*>(Dest);

			for (size_t i = 0; i < Count; ++i)
			{
				destPtr[i] = static_cast<uint8>(Value);
			}

			return Dest;
		}
	} // namespace Memory

	namespace TypeTraits {

	} // namespace TypeTraits
}