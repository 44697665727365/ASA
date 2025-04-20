#include "pch.h"

#include "Game/SDK/Engine_classes.hpp"

bool InitEngine(uint64_t Objects, uint64_t AppendString, uint64_t World, uint64_t ProcessEvent, uint64_t StaticFindObj)
{
    SDK::Offsets::GWorld = World;
    SDK::Offsets::GObjects = Objects;
    SDK::Offsets::AppendString = AppendString;
    SDK::Offsets::ProcessEvent = ProcessEvent;
    SDK::UObject::StaticFindObjectFn = reinterpret_cast<decltype(SDK::UObject::StaticFindObjectFn)>(StaticFindObj);

    return (SDK::Offsets::GWorld && SDK::Offsets::GObjects && SDK::Offsets::AppendString && SDK::Offsets::ProcessEvent);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        uint64_t GObjects = signature(__("48 8D 05 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? 48 8D 0D ? ? ? ? 48 89 05 ? ? ? ? C6 05")).instruction(3).add(7).GetPointer();
        uint64_t AppendStrings = signature(__("48 89 5C 24 ? 57 48 83 EC ? 48 8B F9 48 8B DA ? ? E8 ? ? ? ? 48 8B D3")).GetPointer();
        uint64_t GWorld = signature(__("48 8B 05 ? ? ? ? EB ? 48 8B CF")).instruction(3).add(7).GetPointer();
        uint64_t ProcessEvent = signature(__("40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 89 9D ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C5 48 89 85 ? ? ? ? 4D 8B E0")).GetPointer();
        uint64_t StaticFindObject = signature(__("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 83 FA")).GetPointer();
        if (InitEngine(GObjects, AppendStrings, GWorld, ProcessEvent, StaticFindObject))
        {
            AllocConsole();
            FILE* Dummy;
            freopen_s(&Dummy, "CONOUT$", "w", stdout);
            freopen_s(&Dummy, "CONIN$", "r", stdin);

            uint64_t ReAllocAddr = signature("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F1 41 8B D8 48 8B 0D").GetPointer();
            FMemory::Init(reinterpret_cast<void*>(ReAllocAddr));

            uint64_t DrawTransitionPointer = signature(__("48 89 74 24 ? 48 89 7C 24 ? 55 48 8B EC 48 83 EC 50 80 B9 ? ? ? ? ? 48 8B F2 48 8B F9 0F 85 ? ? ? ? 8B 41 08")).GetPointer();
            Hooks::DrawTransition = (Hooks::DrawTransition_t(DrawTransitionPointer));
            SwapVtable(SDK::UWorld::GetWorld()->OwningGameInstance->LocalPlayers[0]->ViewportClient, 0x76, Hooks::DrawTransition_f);

            Render::DrawTextPtr = signature(__("48 8B C4 48 81 EC ? ? ? ? 83 60")).GetPointer();
            Get::AActorGetTransformPtr = signature(__("48 8B 81 ? ? ? ? 48 85 C0 74 07 48 05 ? ? ? ?")).GetPointer();
        }
    }

    return TRUE;
}