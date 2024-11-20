#pragma once
#include "vec2.hh"
#include "vec3.hh"
#include "../export.hh"

template <typename T>
struct triangle2D
{
  COMMONS_API constexpr triangle2D() = default;
  COMMONS_API constexpr triangle2D(vec2<T> a, vec2<T> b, vec2<T> c) :
  a(a), b(b), c(c)
  {}
  
  vec2<T> a, b, c;
};

template <typename T>
struct triangle3D
{
  COMMONS_API constexpr triangle3D() = default;
  COMMONS_API constexpr triangle3D(vec3<T> a, vec3<T> b, vec3<T> c) :
  a(a), b(b), c(c)
  {}
  
  vec3<T> a, b, c;
};
