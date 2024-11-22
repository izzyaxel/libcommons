#pragma once

#include "linesegment.hh"

/// A mathematical circle
template<typename T>
struct circle
{
  constexpr circle() = default;

  constexpr circle(const vec2<T>& center, const T radius)
  {
    this->center = center;
    this->radius = radius;
  }

  /// Reconstruct this circle
  void construct(const vec2<T>& center, const T radius)
  {
    this->center = center, this->radius = radius;
  }

  vec2<T> center;
  T radius;
};
