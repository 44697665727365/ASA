#include "pch.h"
#include "Getters.h"

namespace Get
{
    SDK::UWorld* World()
    {
        if (SDK::UWorld* W = SDK::UWorld::GetWorld())
            return W;

        return nullptr;
    }

    SDK::UGameInstance* GameInstance()
    {
        if (SDK::UGameInstance* GI = World()->OwningGameInstance)
            return GI;

        return nullptr;
    }

    SDK::ULocalPlayer* LocalPlayer()
    {
        if (SDK::ULocalPlayer* LP = GameInstance()->LocalPlayers[0])
            return LP;

        return nullptr;
    }

    SDK::APlayerController* PlayerController()
    {
        if (SDK::APlayerController* PC = LocalPlayer()->PlayerController)
            return PC;

        return nullptr;
    }

    SDK::AShooterPlayerController* ShooterPlayerController()
    {
        if (SDK::AShooterPlayerController* SPC = static_cast<SDK::AShooterPlayerController*>(PlayerController()))
            return SPC;

        return nullptr;
    }

    SDK::AShooterCharacter* Self()
    {
        if (SDK::AShooterCharacter* SC = ShooterPlayerController()->GetPlayerCharacter())
            return SC;

        return nullptr;
    }

    bool WorldToScreen(SDK::FVector WorldIn, SDK::FVector2D& ScreenOut)
    {
        if (!SDK::UCanvas::Canvas)
            return false;

        SDK::FVector Projected = SDK::UCanvas::Canvas->K2_Project(WorldIn);
        if (!Projected.IsValidVector() || Projected.Z <= 0.f)
            return false;

        ScreenOut = { Projected.X, Projected.Y };

        const SDK::FVector2D ScreenSize(static_cast<double>(SDK::UCanvas::Canvas->SizeX), static_cast<double>(SDK::UCanvas::Canvas->SizeY));

        return (Projected.X >= 0.f && Projected.X <= ScreenSize.X &&
            Projected.Y >= 0.f && Projected.Y <= ScreenSize.Y);
    }
}