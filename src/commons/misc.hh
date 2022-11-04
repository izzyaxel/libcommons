#pragma once

#include <string>
#include "export.hh"

[[nodiscard]] EXPORT std::string getCWD();

[[nodiscard]] EXPORT std::string ptrToString(void *ptr);

template <typename T> [[nodiscard]] T bound(T val, T lower, T upper)
{
	if(val < lower) return lower;
	if(val > upper) return upper;
	return val;
}
