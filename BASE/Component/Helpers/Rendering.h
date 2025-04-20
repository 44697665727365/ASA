#pragma once

namespace Render
{
	static inline uint64 DrawTextPtr = 0x00000000;

	enum Flags_ : uint32
	{
		NONE = 0,

		Left = 1 << 0,
		CenterVertical = 1 << 1,
		Right = 1 << 2,
		Top = 1 << 3,
		CenterHorizontal = 1 << 4,
		Bottom = 1 << 5,
		Center = CenterVertical | CenterHorizontal,

		Bold = 1 << 6,
		Outline = 1 << 7,
		Corners = 1 << 8,
		Inverse = 1 << 9,

		MAX
	} RFlags;
	void Set(Flags_& Flags, Flags_ Bit);
	void Unset(Flags_& Flags, Flags_ Bit);
	void Toggle(Flags_& Flags, Flags_ Bit);
	bool Has(Flags_ Flags, Flags_ Bit);
	void SetAll(Flags_& Flags, uint32_t Bits);
	void UnsetAll(Flags_& Flags, uint32_t Bits);

	void Measure(const std::wstring& Text, SDK::FVector2D& OutSize, SDK::UFont* Font = nullptr, float Scale = 1.f);
	void Text(const std::wstring& Text, SDK::FVector2D Position, SDK::FColor Color, SDK::UFont* Font = nullptr, float Scale = 1.f, Flags_ Flag = NONE);
	void Rect(SDK::FVector2D Position, SDK::FVector2D Size, SDK::FLinearColor BackgroundCol, SDK::UTexture2D* Texture = nullptr, SDK::EBlendMode Blend = SDK::EBlendMode::BLEND_MAX, bool bBorderOnly = false, float BorderThickness = 1.f, SDK::FLinearColor BorderCol = SDK::FLinearColor(1.f, 1.f, 1.f, 1.f), Flags_ Flags = NONE);
}
