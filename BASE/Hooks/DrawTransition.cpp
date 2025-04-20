#include "pch.h"
#include "HookDefs.h"

std::once_flag Once;
namespace Hooks
{
	DrawTransition_t DrawTransition;
    void DrawTransition_f(SDK::UGameViewportClient* Viewport, SDK::UCanvas* Canvas)
    {
        if (!Viewport || !Canvas)
            return DrawTransition(Viewport, Canvas);
        DrawTransition(Viewport, Canvas);
        SDK::UCanvas::Canvas = Canvas;

        std::call_once(Once, []() {
            ComponentLoader::OnLoad();
        });

        //

        ComponentLoader::OnFrame();
        ComponentLoader::OnEntity();

        //
        
        ComponentLoader::OnFrameStart();

        //

        ComponentLoader::OnFrameEnd();

        //if (SDK::UObject::GObjects)
        //{
        //    for (int i = 0; i < SDK::UObject::GObjects->Num(); i++)
        //    {
        //        SDK::UObject* Obj = SDK::UObject::GObjects->GetByIndex(i);
        //
        //        if (!Obj)
        //            continue;
        //
        //        if (Obj->IsDefaultObject())
        //            continue;
        //
        //        printf("Object: %s\n", Obj->GetName().c_str());
        //    }
        //}
    }
}