#pragma once

#if defined(WINDOWS) && defined(SHAREDBUILD)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT 
#endif
