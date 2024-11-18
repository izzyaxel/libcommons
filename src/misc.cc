#include "commons/misc.hh"
#include "commons/stringtools.hh"

#include <sstream>
#include <codecvt>
#include <locale>

#if defined(WINDOWS)
#include <windows.h>
#include <libloaderapi.h>
#elif defined(LINUX) || defined(OSX)
#include <sys/stat.h>
#include <unistd.h>
#endif

std::string getCWD()
{
  #if defined(WINDOWS)
  wchar_t rawdir[2048];
  GetModuleFileNameW(nullptr, rawdir, 2048);
  std::string exeDir = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(std::wstring(rawdir));
  exeDir = replaceAll(exeDir, '\\', '/');
  return exeDir.substr(0, exeDir.find_last_of('/')) + "/";
  #elif defined(LINUX)
  char dir[2048];
  return getcwd(dir, 2048) == nullptr ? "" : std::string{dir} + "/";
  #endif
}

std::string ptrToString(const void* ptr)
{
  std::stringstream ss{};
  ss << ptr;
  return ss.str();
}
