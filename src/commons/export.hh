#pragma once

#if defined(WINDOWS) && defined(SHAREDBUILD)
#define COMMONSAPI __declspec(dllexport)
#else
#define COMMONSAPI 
#endif
