#pragma once
#include "vec3.hh"

template<typename T>
struct sphere
{
  constexpr sphere() = default;
  
  constexpr sphere(const vec3<T>& center, T radius) :
  center(center), radius(radius)
  {}

  [[nodiscard]] bool isIntersecting(const sphere<T>& other) const
  {
    return this->radius + other.radius >= distance3D(this->center, other.center);
  }

  vec3<T> center;
  T radius;
};
