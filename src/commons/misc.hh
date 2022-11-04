#pragma once

#include <string>
#include "export.hh"

[[nodiscard]] COMMONSAPI std::string getCWD();

[[nodiscard]] COMMONSAPI std::string ptrToString(void *ptr);

template <typename T> [[nodiscard]] T bound(T val, T lower, T upper)
{
	if(val < lower) return lower;
	if(val > upper) return upper;
	return val;
}
