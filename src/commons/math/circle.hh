#pragma once

#include "linesegment2D.hh"
#include "aabb.hh"
#include "general.hh"

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

  /// Circle-circle collision
  [[nodiscard]] bool isIntersecting(const circle<T>& other) const
  {
    return this->radius + other.radius >= distance2D(this->center, other.center);
  }

  /// Circle-line
  [[nodiscard]] bool isIntersecting(const linesegment2D<T>& other) const
  {
    const T dX = other.point2.x() - other.point1.x();
    const T dY = other.point2.y() - other.point1.y();
    const T dR = std::sqrt((dX * dX) + (dY * dY));
    const T D = (other.point1.x() * other.point2.y()) - (other.point2.x() * other.point1.y());
    const T incidence = (this->radius * this->radius) * (dR * dR) - (D * D);
    if(incidence < 0)
    {
      return false;
    }
    if(incidence == 0)
    {
      return false;
    }
    //TODO finish
    /*outFirst.x() = ((D * dY) + sign<T>(dY) * dX * std::sqrt(((this->radius * this->radius) * (dR * dR)) - (D * D))) / (dR * dR);
    outFirst.y() = ((-D * dX) + std::abs(dY) * std::sqrt(((this->radius * this->radius) * (dR * dR)) - (D * D))) / (dR * dR);
    outSecond.x() = ((D * dY) - sign<T>(dY) * dX * std::sqrt(((this->radius * this->radius) * (dR * dR)) - (D * D))) / (dR * dR);
    outSecond.y() = ((-D * dX) - std::abs(dY) * std::sqrt(((this->radius * this->radius) * (dR * dR)) - (D * D))) / (dR * dR);*/
    return true;
  }

  /// Circle-aabb collision
  [[nodiscard]] bool isIntersecting(const aabb2D<T>& other) const //TODO optimization
  {
    //broad phase
    if(this->isIntersecting({other.centerX, other.centerY}))
    {
      return true;
    }
    
    const aabb2D<T> broadThis = aabb2D<T>(this->center.x() - this->radius, this->center.x() + this->radius, this->center.y() - this->radius, this->center.y() + this->radius);
    if(!broadThis.isIntersecting(other))
    {
      return false;
    }

    const vec2<T> ul = {other.minX, other.maxY};
    if(this->isIntersecting(ul))
    {
      return true;
    }
    
    const vec2<T> ur = {other.maxX, other.maxY};
    if(this->isIntersecting(ur))
    {
      return true;
    }
    
    const vec2<T> ll = {other.minX, other.minY};
    if(this->isIntersecting(ll))
    {
      return true;
    }
    
    const vec2<T> lr = {other.maxX, other.maxY};
    if(this->isIntersecting(lr))
    {
      return true;
    }

    const linesegment2D<T> top = linesegment2D<T>(ul, ur);
    if(this->isIntersecting(top))
    {
      return true;
    }
    
    const linesegment2D<T> bottom = linesegment2D<T>(ll, lr);
    if(this->isIntersecting(bottom))
    {
      return true;
    }
    
    const linesegment2D<T> right = linesegment2D<T>(ur, lr);
    if(this->isIntersecting(right))
    {
      return true;
    }
    
    const linesegment2D<T> left = linesegment2D<T>(ul, ll);
    return this->isIntersecting(left);
  }

  [[nodiscard]] bool isIntersecting(const vec2<T>& point) const
  {
    return this->radius >= distance2D(point, this->center);
  }

  vec2<T> center;
  T radius;
};
