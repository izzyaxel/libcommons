#pragma once
#include "vec2.hh"
#include "vec3.hh"

template <typename T>
struct quad2D
{
  constexpr quad2D() = default;
  constexpr quad2D(vec2<T> a, vec2<T> b, vec2<T> c, vec2<T> d) :
  a(a), b(b), c(c), d(d)
  {}
  
  vec2<T> a, b, c, d;
};

template <typename T>
struct quad3D
{
  constexpr quad3D() = default;
  constexpr quad3D(vec3<T> a, vec3<T> b, vec3<T> c, vec3<T> d) :
  a(a), b(b), c(c), d(d)
  {}
  
  vec3<T> a, b, c, d;
};
