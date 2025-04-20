#pragma once

namespace Globals
{
	struct VisualsVariables_t
	{
		bool bMaster = true;

		struct Players_t
		{
			bool bMaster = true;

			bool bNames = true;
			bool bDistance = true;
			bool bHealth = true;
			bool bWeight = true;
			bool bTribe = true;

			struct Flags_t
			{
				bool ShowHealthText = true;
				bool ShowTeam = true;
				bool HideSelf = false;
				bool VisibleOnly = true;
				bool ShowOffScreen = true;
				bool TargetOnly = false;
			} Flags;
		} Players;

		struct Dinosaurs_t
		{
			bool bMaster = false;

			struct Flags_t
			{

			} Flags;
		} Dinos;
	}; inline VisualsVariables_t Visuals;
}