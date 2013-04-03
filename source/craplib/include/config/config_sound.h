#include "config/config_platforms.h"

#if defined(CRAP_PLATFORM_WIN)
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#endif