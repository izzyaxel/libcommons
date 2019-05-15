#pragma once

#include <string>

std::string getCWD();

std::string ptrToString(void *ptr);

template <typename T> T bound(T val, T lower, T upper)
{
	if(val < lower) return lower;
	if(val > upper) return upper;
	return val;
}
