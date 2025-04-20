#include "pch.h"
#include "Helpers.h"

namespace Help
{
	uint8 DistanceToAlpha(float Distance)
	{
		constexpr float MaxDistance = 30000.0f;
		constexpr uint8 MinAlpha = 32;

		if (Distance >= MaxDistance)
			return MinAlpha;
		if (Distance <= 0.f)
			return 255;

		float Ratio = 1.0f - (Distance / MaxDistance);
		float Alpha = MinAlpha + Ratio * (255.0f - MinAlpha);

		return static_cast<uint8>(Alpha);
	}

	std::wstring FloatToSingleDec(float Value)
	{
		int IntPt = static_cast<int>(Value);
		int DecimalPt = static_cast<int>((Value - IntPt) * 10);

		return std::to_wstring(IntPt) + L"." + std::to_wstring(DecimalPt);
	}

	bool Safety()
	{
		if (!Get::World())
			return false;

		if (!Get::LocalPlayer())
			return false;

		SDK::APlayerController* PC = Get::PlayerController();
		if (!PC || !PC->PlayerCameraManager || !PC->MyHUD ||
			!PC->AcknowledgedPawn || !PC->AcknowledgedPawn->PlayerState ||
			!PC->AcknowledgedPawn->RootComponent || !PC->AcknowledgedPawn->Controller)
			return false;

		SDK::AShooterCharacter* SC = Get::Self();
		if (!SC || !SC->Mesh)
			return false;

		return true;
	}
}