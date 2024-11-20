#pragma once
#include "../export.hh"
#include "circle.hh"
#include "vec2.hh"
#include "vec3.hh"
#include "aabb.hh"

/// A 2D axis-aligned capsule shape, defined by 2 circles and an aabb
template <typename T>
struct aacapsule2D
{
  COMMONS_API constexpr aacapsule2D() = default;
  
  COMMONS_API constexpr aacapsule2D(const T width, const T height, const vec2<T>& center)
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

  COMMONS_API void move(const vec2<T>& amount)
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

  COMMONS_API void moveTo(const vec2<T>& newCenterPos)
  {
    T width = this->rect.maxX - this->rect.minX;
    T aabbHeight = this->rect.maxY - this->rect.minY;
    T height = aabbHeight + this->circleA.radius;
    this->rect = aabb2D<T>(newCenterPos, {width, aabbHeight});
    const float xCenter = this->rect.minX + ((this->rect.maxX - this->rect.minX) / 2.0f);
    this->circleA = circle<T>(vec2<T>{xCenter, this->rect.maxY}, width);
    this->circleB = circle<T>(vec2<T>{xCenter, this->rect.minY}, width);
  }

  COMMONS_API bool isIntersecting(const vec2<T>& point)
  {
    return this->circleA.isIntersecting(point) || this->circleB.isIntersecting(point) || this->rect.isIntersecting(point);
  }

  COMMONS_API bool isIntersecting(const circle<T>& other)
  {
    return this->circleA.isIntersecting(other) || this->circleB.isIntersecting(other) || this->rect.isIntersecting(other);
  }

  COMMONS_API bool isIntersecting(const aabb2D<T>& other)
  {
    return this->circleA.isIntersecting(other) || this->circleB.isIntersecting(other) || this->rect.isIntersecting(other);
  }

  COMMONS_API bool isIntersecting(const aacapsule2D<T>& other)
  {
    return
      this->circleA.isIntersecting(other.circleA) || this->circleB.isIntersecting(other.circleB) ||
      this.rect.isIntersecting(other.rect) || this->circleA.isIntersecting(other.circleB) ||
      this->rect.isIntersecting(other.circleA) || this->rect.isIntersecting(other.circleB) ||
      other.rect.isIntersecting(this->circleA) || other.rect.isIntersecting(this->circleB);
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
