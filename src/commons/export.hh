#pragma once

#if defined(WINDOWS) && defined(SHAREDBUILD)
#define COMMONS_API __declspec(dllexport)
#else
#define COMMONS_API 
#endif
