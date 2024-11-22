#pragma once
#include "vec3.hh"

template<typename T>
struct sphere
{
  constexpr sphere() = default;
  
  constexpr sphere(const vec3<T>& center, T radius) :
  center(center), radius(radius)
  {}

  vec3<T> center;
  T radius;
};
