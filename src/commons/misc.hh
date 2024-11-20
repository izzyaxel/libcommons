#pragma once

#include <string>

[[nodiscard]] std::string getCWD();

[[nodiscard]] std::string ptrToString(void* ptr);

template <typename T> [[nodiscard]] T bound(const T val, const T lower, const T upper)
{
  if(val < lower) return lower;
  if(val > upper) return upper;
  return val;
}
