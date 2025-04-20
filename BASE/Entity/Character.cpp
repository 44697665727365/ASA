#include "pch.h"

namespace Characters
{
	namespace Helpers
	{
		std::tuple<bool, SDK::FVector2D, SDK::FVector2D> WorldToHeadRoot(SDK::AShooterCharacter* Shooter)
		{
			int32 HeadBoneIndex = 8;
			int32 RootBoneIndex = 0;
			constexpr float HeadZOffset = 18.f;
			constexpr float RootZOffset = -5.f;

			SDK::FVector HeadIn = Shooter->Mesh->GetBoneLocation(HeadBoneIndex);
			if (!HeadIn.IsValidVector())
				return { false, {}, {} };
			//HeadIn.Z += HeadZOffset;

			SDK::FVector RootIn = Shooter->Mesh->GetBoneLocation(RootBoneIndex);
			if (!RootIn.IsValidVector())
				return { false, {}, {} };
			//RootIn.Z += RootZOffset;

			SDK::FVector2D HeadOut, RootOut;

			if (!Get::WorldToScreen(HeadIn, HeadOut))
				return { false, {}, {} };
			if (!Get::WorldToScreen(RootIn, RootOut))
				return { false, {}, {} };

			return { true, HeadOut, RootOut };
		}

		SDK::FLinearColor HSVToRGB(float H, float S, float V, uint8 Alpha = 255)
		{
			float C = V * S;
			float X = C * (1.0f - FreeCRT::Math::AbsF(FreeCRT::Math::FmodF(H / 60.0f, 2) - 1.0f));
			float M = V - C;

			float R = 0, G = 0, B = 0;

			if (H < 60) { R = C; G = X; B = 0; }
			else if (H < 120) { R = X; G = C; B = 0; }
			else if (H < 180) { R = 0; G = C; B = X; }
			else if (H < 240) { R = 0; G = X; B = C; }
			else if (H < 300) { R = X; G = 0; B = C; }
			else { R = C; G = 0; B = X; }

			return SDK::FLinearColor::FromARGB(Alpha, static_cast<uint8>((R + M) * 255), static_cast<uint8>((G + M) * 255), static_cast<uint8>((B + M) * 255));
		}
	}

	void Cheater(SDK::AShooterCharacter* Shooter, float& NewY)
	{

	}

	void Healthbar(SDK::AShooterCharacter* Shooter, float& NewY, uint8 FontFade)
	{
		if (!Shooter)
			return;

		auto [Ret, Head, Root] = Helpers::WorldToHeadRoot(Shooter);
		if (!Ret)
			return;

		float CurHealthF = Shooter->ReplicatedCurrentHealth;
		float MaxHealthF = Shooter->ReplicatedMaxHealth;
		float PerHealthF = CurHealthF / MaxHealthF;

		std::wstring HealthStr = Help::FloatToSingleDec(CurHealthF);
		bool bShowHealthValue = Globals::Visuals.Players.Flags.ShowHealthText && !HealthStr.empty();

		SDK::FLinearColor HealthValueCol{};
		float Hue = FreeCRT::TypeTraits::Clamp(PerHealthF, 0.f, 1.f) * 120.f;
		HealthValueCol = Helpers::HSVToRGB(Hue, 1.f, 1.f, FontFade);

		SDK::FVector2D HealthTextSize{};
		Render::Measure(HealthStr, HealthTextSize);

		Render::Flags_ RFlags = Render::NONE;
		Render::SetAll(RFlags, Render::Outline | Render::CenterHorizontal);

		Render::Rect(SDK::FVector2D(Root.X, (Head.Y + ((HealthTextSize.Y * .5f) - 3.333333f)) - NewY), SDK::FVector2D(40.f, 5.f), SDK::FLinearColor::FromARGB(200, 28, 28, 28), nullptr, SDK::EBlendMode::BLEND_MAX, false, 1.f, SDK::FLinearColor::FromRGB(0, 0, 0), RFlags);
		Render::Rect(SDK::FVector2D(Root.X - 20.f, (Head.Y + ((HealthTextSize.Y * .5f) - 3.333333f)) - NewY), SDK::FVector2D(40.f * PerHealthF, 5.f), HealthValueCol);

		if (bShowHealthValue)
			Render::Text(HealthStr, SDK::FVector2D(Root.X, Head.Y - NewY), SDK::FColor(255, 255, 255, FontFade), nullptr, .75f, Render::CenterHorizontal);

		NewY += HealthTextSize.Y;
	}

	void Torporbar(SDK::AShooterCharacter* Shooter, float& NewY)
	{

	}

	void Equipment(SDK::AShooterCharacter* Shooter, float& NewY)
	{

	}

	void DistanceName(SDK::AShooterCharacter* Shooter, float& NewY, uint8 FontFade)
	{
		if (!Shooter)
			return;

		auto [Ret, Head, Root] = Helpers::WorldToHeadRoot(Shooter);
		if (!Ret)
			return;

		float DistanceF = Shooter->N_GetActorLocation().GetDistanceTo(Get::Self()->N_GetActorLocation()) / 100;
		std::wstring DistanceStr = Globals::Visuals.Players.bDistance && (DistanceF > 0.0f) ? __(L"[") + Help::FloatToSingleDec(DistanceF) + __(L"M]") : __(L"");
		std::wstring NamesStr = Globals::Visuals.Players.bNames ? Shooter->PlayerName.ToWString() : __(L"");
		if (DistanceStr.empty() && NamesStr.empty())
			return;

		SDK::FColor DistanceCol = SDK::FColor(0, 255, 255, FontFade);
		SDK::FColor NamesCol = SDK::FColor(255, 255, 255, FontFade);

		SDK::FVector2D TotalSize{}, DistanceSize{}, NamesSize{}, RenderPos{};

		if (!DistanceStr.empty())
			Render::Measure(DistanceStr, DistanceSize);
		if (!NamesStr.empty())
			Render::Measure(NamesStr, NamesSize);

		TotalSize.X = DistanceSize.X + NamesSize.X + (!DistanceStr.empty() && !NamesStr.empty() ? 5.f : 0.f);
		TotalSize.Y = FreeCRT::Math::Max(DistanceSize.Y, NamesSize.Y);

		RenderPos = SDK::FVector2D(Root.X - TotalSize.X * .5f, Head.Y - NewY);

		if (!DistanceStr.empty())
		{
			Render::Text(DistanceStr, RenderPos, DistanceCol);
			RenderPos.X += DistanceSize.X + (!NamesStr.empty() ? 5.f : 0.f);
		}

		if (!NamesStr.empty())
			Render::Text(NamesStr, RenderPos, NamesCol);

		NewY += TotalSize.Y;
	}

	void Bones(SDK::AShooterCharacter* Shooter)
	{

	}

	void TribeWeight(SDK::AShooterCharacter* Shooter, float& NewY, uint8 FontFade)
	{
		if (!Shooter)
			return;

		auto [Ret, Head, Root] = Helpers::WorldToHeadRoot(Shooter);
		if (!Ret)
			return;

		std::wstring TribeStr = Globals::Visuals.Players.bTribe ? Shooter->TribeName.ToWString() : __(L"");
		std::wstring WeightStr = Globals::Visuals.Players.bWeight && (Shooter->ReplicatedWeight > 0.0f) ? __(L"(") + Help::FloatToSingleDec(Shooter->ReplicatedWeight) + __(L"lbs)") : __(L"");
		if (TribeStr.empty() && WeightStr.empty())
			return;

		SDK::FColor TribeCol = SDK::FColor(255, 0, 0, FontFade);
		SDK::FColor WeightCol = SDK::FColor(200, 200, 200, FontFade);

		SDK::FVector2D TotalSize{}, TribeSize{}, WeightSize{}, RenderPos{};

		if (!TribeStr.empty())
			Render::Measure(TribeStr, TribeSize);
		if (!WeightStr.empty())
			Render::Measure(WeightStr, WeightSize);

		TotalSize.X = TribeSize.X + WeightSize.X + (!TribeStr.empty() && !WeightStr.empty() ? 5.f : 0.f);
		TotalSize.Y = FreeCRT::Math::Max(TribeSize.Y, WeightSize.Y);

		RenderPos = SDK::FVector2D(Root.X - TotalSize.X * .5f, Head.Y - NewY);

		if (!TribeStr.empty())
		{
			Render::Text(TribeStr, RenderPos, TribeCol);
			RenderPos.X += TribeSize.X + (!WeightStr.empty() ? 5.f : 0.f);
		}

		if (!WeightStr.empty())
			Render::Text(WeightStr, RenderPos, WeightCol);

		NewY += TotalSize.Y;
	}

	void SteamImplant(SDK::AShooterCharacter* Shooter, float& NewY)
	{

	}

	void Lines(SDK::AShooterCharacter* Shooter, float& NewY)
	{

	}

	void Angle(SDK::AShooterCharacter* Shooter)
	{

	}

	// *CHEATER*
	// [Health]
	// Equipment
	// Name [Distance]
	// Bones
	// (Weight) Tribe
	// Steam Implant

	void RenderCharacters(SDK::AActor* Actors)
	{
		float Y = 0;

		if (!Actors)
			return;

		SDK::AShooterCharacter* Shooter = static_cast<SDK::AShooterCharacter*>(Actors);

		uint8 FontFadingDistance = Help::DistanceToAlpha(Shooter->N_GetActorLocation().GetDistanceTo(Get::Self()->N_GetActorLocation()));

		Healthbar(Shooter, Y, FontFadingDistance);
		DistanceName(Shooter, Y, FontFadingDistance);
		TribeWeight(Shooter, Y, FontFadingDistance);
	}

	void Start()
	{

	}

	void End()
	{

	}

	class Component : public ComponentInterface
	{
	public:
		bool IsSupported()
		{
			bool bState = Help::Safety();
			if (!bState)
				return false;
			
			return true;
		}

		void OnFrameStart()
		{
			Characters::Start();
		}

		void OnFrameEnd()
		{
			Characters::End();
		}

		void OnFrame()
		{

		}

		void OnLoad()
		{

		}

		void OnEntity(SDK::AActor* Actors)
		{
			if (!Actors || !Actors->RootComponent)
				return;

			if (!Globals::Visuals.bMaster)
				return;
			
			if (!Actors->IsA(SDK::AShooterCharacter::StaticClass()))
				return;
			
			SDK::AShooterCharacter* Character = static_cast<SDK::AShooterCharacter*>(Actors);
			
			if (Globals::Visuals.Players.bMaster)
				Characters::RenderCharacters(Character);
		}
	};
} REGISTER_COMPONENT(Characters::Component);