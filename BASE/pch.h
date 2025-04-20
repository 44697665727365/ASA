#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "framework.h"

#undef ARRAYSIZE
#define ARRAYSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "urlmon.lib")

using namespace std::chrono_literals;
using namespace std::literals;

#pragma warning( disable : 4244 ) //Disable int to float warning
#pragma warning( disable : 4267 ) //Disable size_t to int warning
#pragma warning( disable : 4305 ) //Disable double to float warning
#pragma warning( disable : 26495 ) //Disable Variable uninitalized for my ui stuff
#pragma warning( disable : 26812 ) //Disable enum type is unscoped
#pragma warning( disable : 4838 ) //Disable double to float narrowing
#pragma warning( disable : 4099 ) //Disable class -> struct 

#include "Utilities/CRT/FreeCRT.h"

//#include "Utilities/Protection/LazyImport.h"
#include "Utilities/Protection/Xors.h"

#include "Utilities/Memory/memory.h"
//#include "Utilities/string.h"
#include "Utilities/Signature/signature.h"

#include "Game/SDK.hpp"
#include "Component/Helpers/GlobalVariables.h"
#include "Component/Helpers/Rendering.h"
#include "Component/Helpers/Getters.h"
#include "Component/Helpers/Helpers.h"

#include "Component/ComponentLoader.h"

#include "Hooks/HookDefs.h"

#endif //PCH_H

