#include "commons/misc.hh"
#include "commons/stringtools.hh"

#include <sstream>
#include <filesystem>

std::string getCWD()
{
  return std::filesystem::current_path().string();
}

std::string ptrToString(const void* ptr)
{
  std::stringstream ss{};
  ss << ptr;
  return ss.str();
}
