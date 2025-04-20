#pragma once

class ComponentInterface
{
public:
    virtual ~ComponentInterface() = default;

    virtual bool IsSupported()
    {
        return true;
    }

    virtual void OnFrameStart() {}
    virtual void OnFrameEnd() {}
    virtual void OnFrame() {}
    virtual void OnLoad() {}
    virtual void OnEntity(SDK::AActor* actor) {}
};
