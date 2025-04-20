#include "pch.h"
#include "Rendering.h"

namespace Render
{
	void Set(Flags_& Flags, Flags_ Bit)
	{
		Flags = static_cast<Flags_>(static_cast<uint32_t>(Flags) | static_cast<uint32_t>(Bit));
	}

	void Unset(Flags_& Flags, Flags_ Bit)
	{
		Flags = static_cast<Flags_>(static_cast<uint32_t>(Flags) & ~static_cast<uint32_t>(Bit));
	}

	void Toggle(Flags_& Flags, Flags_ Bit)
	{
		Flags = static_cast<Flags_>(static_cast<uint32_t>(Flags) ^ static_cast<uint32_t>(Bit));
	}

	bool Has(Flags_ Flags, Flags_ Bit)
	{
		return (static_cast<uint32_t>(Flags) & static_cast<uint32_t>(Bit)) != 0;
	}

	void SetAll(Flags_& Flags, uint32_t Bits)
	{
		Flags = static_cast<Flags_>(static_cast<uint32_t>(Flags) | Bits);
	}

	void UnsetAll(Flags_& Flags, uint32_t Bits)
	{
		Flags = static_cast<Flags_>(static_cast<uint32_t>(Flags) & ~Bits);
	}

	void Measure(const std::wstring& Text, SDK::FVector2D& OutSize, SDK::UFont* Font, float Scale)
	{
		if (!SDK::UCanvas::Canvas)
			return;

		SDK::UFont* UseFont = Font;
		if (!UseFont)
		{
			static SDK::UFont* CachedFont = nullptr;
			if (!CachedFont)
				CachedFont = SDK::UObject::StaticFindObject<SDK::UFont>(__(L"/Game/PrimalEarth/UI/Fonts/OpenSansRegular30-em34.OpenSansRegular30-em34"));

			UseFont = CachedFont;
		}

		OutSize = SDK::UCanvas::Canvas->K2_TextSize(UseFont, Text.data(), SDK::FVector2D(Scale, Scale));
	}

	void Text(const std::wstring& Text, SDK::FVector2D Position, SDK::FColor Color, SDK::UFont* Font, float Scale, Flags_ Flag)
	{
		if (!DrawTextPtr)
			DrawTextPtr = signature(__("48 8B C4 48 81 EC ? ? ? ? 83 60")).GetPointer();

		// __int64 __fastcall sub_146ACB350(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
		// {
		//   return sub_146ACD650(a1, a2, a3, a4, a5, 1232348160, 1232348160, a6, a7, 0, 0);
		// }

		// .text : 0000000146ACB350  sub_146ACB350   proc near          ; CODE XREF : sub_1439D6280 + 9A2?p
		// .text : 0000000146ACB350                                     ; sub_1439D6280 + A21?p ...
		// .text : 0000000146ACB350
		// .text : 0000000146ACB350 var_98 = dword ptr - 98h
		// .text : 0000000146ACB350 var_90 = dword ptr - 90h
		// .text : 0000000146ACB350 var_88 = dword ptr - 88h
		// .text : 0000000146ACB350 var_80 = dword ptr - 80h
		// .text : 0000000146ACB350 var_78 = dword ptr - 78h
		// .text : 0000000146ACB350 var_70 = byte ptr - 70h
		// .text : 0000000146ACB350 var_68 = byte ptr - 68h
		// .text : 0000000146ACB350 var_58 = qword ptr - 58h
		// .text : 0000000146ACB350 arg_20 = dword ptr  28h
		// .text : 0000000146ACB350 arg_28 = dword ptr  30h
		// .text : 0000000146ACB350 arg_30 = dword ptr  38h
		// .text : 0000000146ACB350
		// .text : 0000000146ACB350                 mov     rax, rsp
		// .text : 0000000146ACB353                 sub     rsp, 0B8h
		// .text : 0000000146ACB35A                 and dword ptr[rax - 48h], 0FFFFFFF8h
		// .text : 0000000146ACB35E                 xorps   xmm0, xmm0
		// .text : 0000000146ACB361                 and dword ptr[rax - 40h], 0FFFFFFFEh
		// .text : 0000000146ACB365                 xorps   xmm1, xmm1
		// .text : 0000000146ACB368                 mov     qword ptr[rax - 50h], 0
		// .text : 0000000146ACB370                 movups  xmmword ptr[rax - 3Ch], xmm0
		// .text : 0000000146ACB374                 movups  xmmword ptr[rax - 18h], xmm0
		// .text : 0000000146ACB378                 movss   xmm0, [rsp + 0B8h + arg_30]
		// .text : 0000000146ACB381                 movups  xmmword ptr[rax - 28h], xmm1
		// .text : 0000000146ACB385                 lea     rax, [rax - 48h]
		// .text : 0000000146ACB389                 movss   xmm1, [rsp + 0B8h + arg_28]
		// .text : 0000000146ACB392                 mov[rsp + 0B8h + var_58], rax
		// .text : 0000000146ACB397                 mov[rsp + 0B8h + var_68], 0
		// .text : 0000000146ACB39C                 mov[rsp + 0B8h + var_70], 0
		// .text : 0000000146ACB3A1                 movss[rsp + 0B8h + var_78], xmm0
		// .text : 0000000146ACB3A7                 movss   xmm0, cs : dword_149509114
		// .text : 0000000146ACB3AF                 movss[rsp + 0B8h + var_80], xmm1
		// .text : 0000000146ACB3B5                 movss[rsp + 0B8h + var_88], xmm0
		// .text : 0000000146ACB3BB                 movss[rsp + 0B8h + var_90], xmm0
		// .text : 0000000146ACB3C1                 movss   xmm0, [rsp + 0B8h + arg_20]
		// .text : 0000000146ACB3CA                 movss[rsp + 0B8h + var_98], xmm0
		// .text : 0000000146ACB3D0                 call    sub_146ACD650
		// .text : 0000000146ACB3D5                 add     rsp, 0B8h
		// .text : 0000000146ACB3DC                 retn
		// .text : 0000000146ACB3DC sub_146ACB350   endp

		if (!DrawTextPtr || !SDK::UCanvas::Canvas)
			return;

		SDK::UFont* UseFont = Font;
		if (!UseFont)
		{
			static SDK::UFont* CachedFont = nullptr;
			if (!CachedFont)
				CachedFont = SDK::UObject::StaticFindObject<SDK::UFont>(__(L"/Game/PrimalEarth/UI/Fonts/OpenSansRegular30-em34.OpenSansRegular30-em34"));

			UseFont = CachedFont;
		}

		SDK::FVector2D TextSize(0.f, 0.f);
		Measure(Text, TextSize, UseFont, Scale);

		if (Has(Flag, CenterHorizontal)) Position.X -= (TextSize.X * .5f); // X
		if (Has(Flag, Right))  Position.X -= TextSize.X;                   // X
		if (Has(Flag, CenterVertical)) Position.Y -= (TextSize.Y * .5f);   // Y
		if (Has(Flag, Bottom)) Position.Y -= TextSize.Y;                   // Y

		SDK::UCanvas::Canvas->DrawColor = Color;

		SDK::FString FStr(Text.data());
		auto Func = reinterpret_cast<float(__fastcall*)(SDK::UCanvas * _this, SDK::UFont * InFont, SDK::FString * InText, float X, float Y, float XScale, float YScale)>(DrawTextPtr);
		Func(SDK::UCanvas::Canvas, UseFont, &FStr, Position.X, Position.Y, Scale, Scale);
	}

	void Rect(SDK::FVector2D Position, SDK::FVector2D Size, SDK::FLinearColor BackgroundCol, SDK::UTexture2D* Texture, SDK::EBlendMode Blend, bool bBorderOnly, float BorderThickness, SDK::FLinearColor BorderCol, Flags_ Flags)
	{
		if (!SDK::UCanvas::Canvas)
			return;

		if (Has(Flags, CenterHorizontal)) Position.X -= (Size.X * .5f); // X
		if (Has(Flags, Right))  Position.X -= Size.X;                   // X
		if (Has(Flags, CenterVertical)) Position.Y -= (Size.Y * .5f);   // Y
		if (Has(Flags, Bottom)) Position.Y -= Size.Y;                   // Y

		if (!bBorderOnly)
			SDK::UCanvas::Canvas->K2_DrawTexture(Texture ? Texture : SDK::UCanvas::Canvas->DefaultTexture, Position, Size, SDK::FVector2D(0, 0), SDK::FVector2D(1, 1), BackgroundCol, Blend, 0.f, SDK::FVector2D(0, 0));

		if (Has(Flags, Outline))
			SDK::UCanvas::Canvas->K2_DrawBox(SDK::FVector2D(Position.X - BorderThickness * .5f, Position.Y - BorderThickness * .5f), SDK::FVector2D(Size.X + BorderThickness, Size.Y + BorderThickness), BorderThickness, BorderCol);
	}
}