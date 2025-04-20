#pragma once

namespace Hooks
{
    void RunTableSwaps();

    typedef void(*DrawTransition_t)(SDK::UGameViewportClient* Viewport, SDK::UCanvas* Canvas);
    extern DrawTransition_t DrawTransition;
    void DrawTransition_f(SDK::UGameViewportClient* Viewport, SDK::UCanvas* Canvas);
}