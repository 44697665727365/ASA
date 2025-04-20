#include "pch.h"
#include "ComponentLoader.h"

std::mutex ComponentLoader::componentMutex;

void ComponentLoader::RegisterComponent(std::unique_ptr<ComponentInterface>&& component)
{
    std::lock_guard<std::mutex> lock(componentMutex);
    GetComponents().push_back(FreeCRT::TypeTraits::Move(component));
}

void ComponentLoader::OnFrameStart()
{
    for (const auto& component : GetComponents())
    {
        if (component->IsSupported())
            component->OnFrameStart();
    }
}

void ComponentLoader::OnFrameEnd()
{
    for (const auto& component : GetComponents())
    {
        if (component->IsSupported())
            component->OnFrameEnd();
    }
}

void ComponentLoader::OnFrame()
{
    for (const auto& component : GetComponents())
    {
        if (component->IsSupported())
            component->OnFrame();
    }
}

void ComponentLoader::OnLoad()
{
    for (const auto& component : GetComponents())
    {
        if (component->IsSupported())
            component->OnLoad();
    }
}

void ComponentLoader::OnEntity()
{
    //GlobalVariables& globals = GlobalVariables::GetInstance();
    //if (globals.VisualsManagerVars.HUD.bMaster && globals.VisualsManagerVars.HUD.bServerClientInformation && globals.VisualsManagerVars.HUD.bNearbyAlerts)
    //{
    //    globals.VisualsManagerVars.HUD.Flags.NearbyEnemies = 0;
    //    globals.VisualsManagerVars.HUD.Flags.VisibleEnemies = 0;
    //    globals.VisualsManagerVars.HUD.Flags.NearbyMeks = 0;
    //    globals.VisualsManagerVars.HUD.Flags.NearbyCarchas = 0;
    //}
    //
    //if (!globals.Sanity())
    //    return;

    SDK::UWorld* world = SDK::UWorld::GetWorld();
    if (!world)
        return;

    const auto& components = GetComponents();
    if (components.empty())
        return;

    const SDK::TArray<SDK::ULevel*>& levels = world->Levels;
    for (int32 levelIndex = 0; levelIndex < levels.Num(); levelIndex++)
    {
        SDK::ULevel* level = levels[levelIndex];
        if (!level)
            continue;

        const SDK::TArray<SDK::AActor*>& actors = level->Actors;
        for (int32 actorIndex = 0; actorIndex < actors.Num(); actorIndex++)
        {
            SDK::AActor* actor = actors[actorIndex];
            if (!actor || !actor->RootComponent)
                continue;

            for (const auto& component : components)
            {
                if (component && component->IsSupported())
                {
                    component->OnEntity(actor);
                }
            }
        }
    }
}

std::vector<std::unique_ptr<ComponentInterface>>& ComponentLoader::GetComponents()
{
    using ComponentVector = std::vector<std::unique_ptr<ComponentInterface>>;

    static std::unique_ptr<ComponentVector, void(*)(ComponentVector*)> Components(nullptr, [](ComponentVector* Vector)
        {
            delete Vector;
        });

    if (!Components)
        Components.reset(new ComponentVector);

    return *Components;
}