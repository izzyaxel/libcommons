#pragma once

#include "linesegment2D.hh"
#include "aabb2D.hh"

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
  [[nodiscard]] bool isIntersecting(const circle<T>& other)
  {
    aabb2D<T> broadThis = aabb2D<T>(this->center.x() - this->radius, this->center.x() + this->radius, this->center.y() - this->radius, this->center.y() + this->radius);
    aabb2D<T> broadOther = aabb2D<T>(other.center.x() - other.radius, other.center.x() + other.radius, other.center.y() - other.radius, other.center.y() + other.radius);
    if(!broadThis.isIntersecting(broadOther))
    {
      return false;
    }
    
    T a = (this->center.x() - other.center.x()) * (this->center.x() - other.center.x());
    T b = (this->center.y() - other.center.y()) * (this->center.y() - other.center.y());
    T distance = std::sqrt(a + b);
    return distance < this->radius + other.radius;
  }

  /// Circle-line
  [[nodiscard]] bool isIntersecting(const linesegment2D<T>& other)
  {
    T dX, dY, dR, D, incidence;
    dX = other.point2.x() - other.point1.x();
    dY = other.point2.y() - other.point1.y();
    dR = std::sqrt((dX * dX) + (dY * dY));
    D = (other.point1.x() * other.point2.y()) - (other.point2.x() * other.point1.y());
    incidence = (this->radius * this->radius) * (dR * dR) - (D * D);
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
  [[nodiscard]] bool isIntersecting(const aabb2D<T>& other) //TODO optimization
  {
    //broad phase
    if(this->containsPoint({other.centerX, other.centerY}))
    {
      return true;
    }
    
    aabb2D<T> broadThis = aabb2D<T>(this->center.x() - this->radius, this->center.x() + this->radius, this->center.y() - this->radius, this->center.y() + this->radius);
    if(!broadThis.isIntersecting(other))
    {
      return false;
    }

    vec2<T> ul = {other.minX, other.maxY};
    if(this->containsPoint(ul))
    {
      return true;
    }
    
    vec2<T> ur = {other.maxX, other.maxY};
    if(this->containsPoint(ur))
    {
      return true;
    }
    
    vec2<T> ll = {other.minX, other.minY};
    if(this->containsPoint(ll))
    {
      return true;
    }
    
    vec2<T> lr = {other.maxX, other.maxY};
    if(this->containsPoint(lr))
    {
      return true;
    }

    linesegment2D<T> top = linesegment2D<T>(ul, ur);
    if(this->isIntersecting(top))
    {
      return true;
    }
    
    linesegment2D<T> bottom = linesegment2D<T>(ll, lr);
    if(this->isIntersecting(bottom))
    {
      return true;
    }
    
    linesegment2D<T> right = linesegment2D<T>(ur, lr);
    if(this->isIntersecting(right))
    {
      return true;
    }
    
    linesegment2D<T> left = linesegment2D<T>(ul, ll);
    return this->isIntersecting(left);
  }

  [[nodiscard]] bool containsPoint(const vec2<T>& point)
  {
    T distance = std::sqrt(((this->center.x() - point.x()) * (this->center.x() - point.x())) + ((this->center.y() - point.y()) * (this->center.y() - point.y())));
    return distance < this->radius;
  }

  vec2<T> center;
  T radius;
};
