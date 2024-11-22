#pragma once

#include "vec2.hh"
#include "vec3.hh"

template<typename T>
struct linesegment2D
{
  constexpr linesegment2D() = default;

  constexpr linesegment2D(const vec2<T>& p1, const vec2<T>& p2) : point1(p1), point2(p2)
  {}

  /// Reconstruct this line segment
  void construct(const vec2<T>& p1, const vec2<T>& p2)
  {
    this->point1 = p1;
    this->point2 = p2;
  }

  [[nodiscard]] vec2<T> getNormal()
  {
    vec2<T> vec = this->point1 - this->point2;
    vec.normalize();
    return {-vec.y(), vec.x()};
  }

  vec2<T> point1, point2;
};

template<typename T>
struct linesegment3D
{
  constexpr linesegment3D() = default;

  constexpr linesegment3D(const vec3<T>& p1, const vec3<T>& p2) : point1(p1), point2(p2)
  {}

  /// Reconstruct this line segment
  void construct(const vec3<T>& p1, const vec3<T>& p2)
  {
    this->point1 = p1;
    this->point2 = p2;
  }

  vec3<T> point1, point2;
};
