#pragma once

namespace Get
{
	static inline uint64 AActorGetTransformPtr = 0x00000000;

	SDK::UWorld* World();
	SDK::UGameInstance* GameInstance();
	SDK::ULocalPlayer* LocalPlayer();
	SDK::APlayerController* PlayerController();
	SDK::AShooterPlayerController* ShooterPlayerController();
	SDK::AShooterCharacter* Self();

	bool WorldToScreen(SDK::FVector WorldIn, SDK::FVector2D& ScreenOut);
	bool IsFriendly(SDK::AActor* Actor);
	bool IsVisible(SDK::AActor* Actor, bool bBone = false, wchar_t BoneName = L' ');
	bool InBounds(SDK::AActor* Actor, SDK::FVector Origin, SDK::FVector2D Screen, float Scale, bool bRect = false);
}
