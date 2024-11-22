#pragma once

#include "circle.hh"
#include "vec2.hh"
#include "vec3.hh"
#include "aabb.hh"

/// A 2D axis-aligned capsule shape, defined by 2 circles and an aabb
template <typename T>
struct aacapsule2D
{
  constexpr aacapsule2D() = default;
  
  constexpr aacapsule2D(const T width, const T height, const vec2<T>& center)
  {
    if(width == height)
    {
      return;
    }
    const float aabbHeight = height - width;
    if(aabbHeight <= 0)
    {
      return;
    }
    this->rect = aabb2D<T>(center, {width, aabbHeight});
    const float xCenter = this->rect.minX + ((this->rect.maxX - this->rect.minX) / 2.0f);
    this->circleA = circle<T>(vec2<T>{xCenter, this->rect.maxY}, width);
    this->circleB = circle<T>(vec2<T>{xCenter, this->rect.minY}, width);
  }

  void move(const vec2<T>& amount)
  {
    T width = this->rect.maxX - this->rect.minX;
    T aabbHeight = this->rect.maxY - this->rect.minY;
    T height = aabbHeight + this->circleA.radius;
    vec2<T> movedCenter = this->rect.center() + amount;
    this->rect = aabb2D<T>(movedCenter, {width, aabbHeight});
    const float xCenter = this->rect.minX + ((this->rect.maxX - this->rect.minX) / 2.0f);
    this->circleA = circle<T>(vec2<T>{xCenter, this->rect.maxY}, width);
    this->circleB = circle<T>(vec2<T>{xCenter, this->rect.minY}, width);
  }

  void moveTo(const vec2<T>& newCenterPos)
  {
    T width = this->rect.maxX - this->rect.minX;
    T aabbHeight = this->rect.maxY - this->rect.minY;
    T height = aabbHeight + this->circleA.radius;
    this->rect = aabb2D<T>(newCenterPos, {width, aabbHeight});
    const float xCenter = this->rect.minX + ((this->rect.maxX - this->rect.minX) / 2.0f);
    this->circleA = circle<T>(vec2<T>{xCenter, this->rect.maxY}, width);
    this->circleB = circle<T>(vec2<T>{xCenter, this->rect.minY}, width);
  }
  
  circle<T> circleA, circleB;
  aabb2D<T> rect;
};

template <typename T>
struct aacapsule3D
{
  
  //TODO sphere
  aabb3D<T> box;
};
