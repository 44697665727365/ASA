#pragma once
#include "ComponentInterface.h"
#include <vector>
#include <memory>
#include <type_traits>
#include <mutex>

class ComponentLoader final
{
public:
    template <typename T>
    class Installer final
    {

    public:
        Installer()
        {
            ComponentLoader::RegisterComponent(std::make_unique<T>());
        }
    };

    template <typename T>
    static T* Get()
    {
        for (const auto& component : GetComponents())
        {
            if (auto* casted = dynamic_cast<T*>(component.get()))
            {
                return casted;
            }
        }
        return nullptr;
    }

    static void RegisterComponent(std::unique_ptr<ComponentInterface>&& component);

    static void OnFrameStart();
    static void OnFrameEnd();
    static void OnFrame();
    static void OnLoad();
    static void OnEntity();

private:
    static std::vector<std::unique_ptr<ComponentInterface>>& GetComponents();
    static std::mutex componentMutex;
};

#define REGISTER_COMPONENT(Name)                          \
namespace                                                 \
{                                                         \
    static ComponentLoader::Installer<Name> __component;  \
}
