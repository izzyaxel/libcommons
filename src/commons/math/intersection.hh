#pragma once

#include "aabb.hh"
#include "circle.hh"
#include "linesegment.hh"
#include "capsule.hh"
#include "triangle.hh"
#include "quad.hh"
#include "sphere.hh"

//====AABB====//

/// AABB/point intersection test
template <typename T>
[[nodiscard]] bool containsPoint(const aabb2D<T> aabb, const vec2<T>& point)
{
  return point.x() > aabb.minX && point.x() < aabb.maxX && point.y() > aabb.minY && point.y() < aabb.maxY;
}

/// AABB/line segment intersection test
template <typename T>
[[nodiscard]] bool isIntersecting(const aabb2D<T> aabb, const linesegment2D<T>& other, T& closestHit)
{
  T hWidth = (aabb.maxX - aabb.minX) / (T)2, hHeight = (aabb.maxY - aabb.minY) / 2;
  linesegment2D<T> top{
    vec2<T>{aabb.centerX - hWidth, aabb.centerY + hHeight},
    vec2<T>{aabb.centerX + hWidth, aabb.centerY + hHeight}
  },
  bottom{
    vec2<T>{aabb.centerX - hWidth, aabb.centerY - hHeight},
    vec2<T>{aabb.centerX + hWidth, aabb.centerY - hHeight}
  },
  left{
    vec2<T>{aabb.centerX - hWidth, aabb.centerY - hHeight},
    vec2<T>{aabb.centerX - hWidth, aabb.centerY + hHeight}
  },
  right{
    vec2<T>{aabb.centerX + hWidth, aabb.centerY - hHeight},
    vec2<T>{aabb.centerX + hWidth, aabb.centerY + hHeight}
  };
  vec2<T> topInterPt{}, bottomInterPt{}, leftInterPt{}, rightInterPt{};
  const bool topInter = top.isIntersecting(other, topInterPt);
  const bool bottomInter = bottom.isIntersecting(other, bottomInterPt);
  const bool leftInter = left.isIntersecting(other, leftInterPt);
  const bool rightInter = right.isIntersecting(other, rightInterPt);
  const float topDist = distance2D<T>(top.point2, topInterPt);
  const float bottomDist = distance2D<T>(bottom.point2, bottomInterPt);
  const float leftDist = distance2D<T>(left.point2, leftInterPt);
  const float rightDist = distance2D<T>(right.point2, rightInterPt);
  if(topInter || bottomInter || leftInter || rightInter)
  {
    closestHit = std::min(std::min(topDist, bottomDist), std::min(leftDist, rightDist));
  }
    
  return topInter || bottomInter || leftInter || rightInter;
}

/// AABB-AABB intersection test
template <typename T>
[[nodiscard]] bool isIntersecting(const aabb2D<T>& a, const aabb2D<T>& b)
{
  return (a.minX < b.maxX) != (a.maxX < b.minX) && (a.minY < b.maxY) != (a.maxY < b.minY);
}

/// AABB-circle intersection test
template <typename T>
[[nodiscard]] bool isIntersecting(const aabb2D<T>& aabb, const circle<T>& circle)
{
  const aabb2D broadOther = aabb2D(circle.center.x() - circle.radius, circle.center.x() + circle.radius,circle.center.y() - circle.radius, circle.center.y() + circle.radius);
  if(!isIntersecting(aabb, broadOther))
  {
    return false;
  }
  
  vec2<T> ul = aabb.upperLeft();
  vec2<T> ur = aabb.upperRight();
  vec2<T> ll = aabb.lowerLeft();
  vec2<T> lr = aabb.lowerRight();
  T distUL = distance2D<T>(circle.center, ul);
  T distUR = distance2D<T>(circle.center, ur);
  T distLL = distance2D<T>(circle.center, ll);
  T distLR = distance2D<T>(circle.center, lr);
  return distUL < circle.radius || distUR < circle.radius || distLR < circle.radius || distLL < circle.radius;
}

/// 2D AABB/AABB intersection test with offset
template <typename T>
[[nodiscard]] bool predictIntersection(const aabb2D<T>&a, const vec2<T> aOffset, const aabb2D<T>& b)
{
  return (a.minX + aOffset.x() < b.maxX) != (a.maxX + aOffset.x() < b.minX) && (a.minY + aOffset.y() < b.maxY) != (a.maxY + aOffset.y() < b.minY);
}

/// 3D AABB/point intersection test
template <typename T>
[[nodiscard]] bool containsPoint(const aabb3D<T>&aabb, const vec3<T>& point)
{
  return point.x() > aabb.minX && point.x() < aabb.maxX && point.y() > aabb.minY && point.y() < aabb.maxY && point.z() > aabb.minZ && point.z() < aabb.maxZ;
}

/// 3D AABB/AABB intersection test
template <typename T>
[[nodiscard]] bool isIntersecting(const aabb3D<T>&a, const aabb3D<T>& b)
{
  return (a.minX < b.maxX) != (a.maxX < b.minX) && (a.minY < b.maxY) != (a.maxY < b.minY) && (a.minZ < b.maxZ) != (a.maxZ < b.minZ);
}

/// 3D AABB/AABB intersection test with offset
template <typename T>
[[nodiscard]] bool predictIntersection(const aabb3D<T>& a, const vec3<T> aOffset, const aabb3D<T>& b)
{
  return (a.minX + aOffset.x() < b.maxX) != (a.maxX + aOffset.x() < b.minX) &&
         (a.minY + aOffset.y() < b.maxY) != (a.maxY + aOffset.y() < b.minY) &&
         (a.minZ + aOffset.z() < b.maxZ) != (a.maxZ + aOffset.z() < b.minZ);
}

//====Circle====//

/// Circle/circle intersection test
template <typename T>
[[nodiscard]] bool isIntersecting(const circle<T>& a, const circle<T>& b)
{
  return a.radius + b.radius >= distance2D(a.center, b.center);
}

/// Circle/circle intersection, assumes there has been an intersection detected, finds the points at which the intersection occured
template <typename T>
void findIntersectionPoints(const circle<T>& a, const circle<T>& b, vec2<T>& hitA, vec2<T>& hitB)
{
  T centerDist = distance2D(a.center, b.center);
  T centerToChordLength = std::pow(centerDist, 2) - std::pow(b.radius, 2) + std::pow(a.radius, 2) / (2 * centerDist);
  T yHalfLength = 4 * std::pow(centerDist, 2) * std::pow(a.radius, 2) - std::pow(std::pow(centerDist, 2) - std::pow(b.radius, 2) + std::pow(a.radius, 2), 2) / (4 * std::pow(centerDist, 2));
  T cuspsChordLength = (1 / centerDist) * std::sqrt(4 * std::pow(centerDist, 2) * std::pow(a.radius, 2) - std::pow(std::pow(centerDist, 2) - std::pow(b.radius, 2) + std::pow(a.radius, 2), 2));
  hitA = {a.center.x() + centerToChordLength, a.center.y() + yHalfLength};
  hitB = {a.center.x() + centerToChordLength, a.center.y() - yHalfLength};
}

/// Circle/circle intersection test
template <typename T>
[[nodiscard]] bool intersection(const circle<T>& a, const circle<T>& b, const vec2<T>& otherVelocity, T& depth)
{
  const T radii = a.radius + b.radius;
  const T centerDist = distance2D(a.center, b.center);
  if(radii >= centerDist) //A collision is guaranteed
  {
    vec2<T> startPoint = b.center;
    vec2<T> endPoint = b.center + otherVelocity;
    linesegment2D<T> velLine{startPoint, endPoint};
    if(centerDist + std::min(a.radius, b.radius) < std::max(a.radius, b.radius)) //One circle is entirely inside the other
    {
      vec2<T> hitA{}, hitB{};
      const bool intersects = a.intersection(velLine, hitA, hitB);
      if(!intersects || (hitA.x() == 0 && hitA.y() == 0 && hitB.x() == 0 && hitB.y() == 0))
      {
        return false;
      }
      
      if(hitA.x() == 0 && hitA.y() == 0)
      {
        depth = distance2D(hitB, endPoint);
      }
      else if(hitB.x() == 0 && hitB.y() == 0)
      {
        depth = distance2D(hitA, endPoint);
      }
      return true;
    }
    //TODO find intersection points, find which ones earlier on the velocity vector, that's the tangency point
    //TODO find point on velocity vector that's 1 moving circle radius away from tangency point
    //TODO distance between that point and the end of the velocity vector is the intersection depth
    
    return true;
  }
  return false;
}

/// Circle/line intersection test
template <typename T>
[[nodiscard]] bool isIntersecting(const circle<T>& circle, const linesegment2D<T>& other)
{
  const T dX = other.point2.x() - other.point1.x();
  const T dY = other.point2.y() - other.point1.y();
  const T dR = std::sqrt(std::pow(dX, 2) + std::pow(dY, 2));
  const T determinant = (other.point1.x() * other.point2.y()) - (other.point2.x() * other.point1.y());
  const T delta = std::pow(circle.radius, 2) * std::pow(dR, 2) - std::pow(determinant, 2);
  if(delta < 0)
  {
    return false;
  }
  return true;
}

/// Circle/line intersection test
template <typename T>
[[nodiscard]] bool intersection(const circle<T>& circle, const linesegment2D<T>& other, vec2<T>& hitA, vec2<T>& hitB)
{
  const T dX = other.point2.x() - other.point1.x();
  const T dY = other.point2.y() - other.point1.y();
  const T dR = std::sqrt(std::pow(dX, 2) + std::pow(dY, 2));
  const T determinant = (other.point1.x() * other.point2.y()) - (other.point2.x() * other.point1.y());
  const T incidence = (circle.radius * circle.radius) * (dR * dR) - (determinant * determinant);
  hitA = {(determinant * dY + sign(dY) * dX * incidence) / (dR * dR), (-determinant * dX + std::abs(dY) * dY) / (dR * dR)};
  hitB = {(determinant * dY - sign(dY) * dX * incidence) / (dR * dR), (-determinant * dX - std::abs(dY) * dY) / (dR * dR)};
  const T delta = (circle.radius * circle.radius) * (dR * dR) - (determinant * determinant);
  if(delta < 0)
  {
    return false;
  }
  return true;
}

/// Circle/aabb intersection test
template <typename T>
[[nodiscard]] bool isIntersecting(const circle<T>& circle, const aabb2D<T>& aabb) //TODO optimization
{
  //broad phase
  if(circle.isIntersecting({aabb.centerX, aabb.centerY}))
  {
    return true;
  }
  
  const aabb2D<T> broadThis = aabb2D<T>(circle.center.x() - circle.radius, circle.center.x() + circle.radius, circle.center.y() - circle.radius, circle.center.y() + circle.radius);
  if(!broadThis.isIntersecting(aabb))
  {
    return false;
  }

  const vec2<T> ul = {aabb.minX, aabb.maxY};
  if(isIntersecting(circle, ul))
  {
    return true;
  }
  
  const vec2<T> ur = {aabb.maxX, aabb.maxY};
  if(isIntersecting(circle, ur))
  {
    return true;
  }
  
  const vec2<T> ll = {aabb.minX, aabb.minY};
  if(isIntersecting(circle, ll))
  {
    return true;
  }
  
  const vec2<T> lr = {aabb.maxX, aabb.maxY};
  if(isIntersecting(circle, lr))
  {
    return true;
  }

  const linesegment2D<T> top = linesegment2D<T>(ul, ur);
  if(isIntersecting(circle, top))
  {
    return true;
  }
  
  const linesegment2D<T> bottom = linesegment2D<T>(ll, lr);
  if(isIntersecting(circle, bottom))
  {
    return true;
  }
  
  const linesegment2D<T> right = linesegment2D<T>(ur, lr);
  if(isIntersecting(circle, right))
  {
    return true;
  }
  
  const linesegment2D<T> left = linesegment2D<T>(ul, ll);
  return isIntersecting(circle, left);
}

/// Circle/point intersection test
template<typename T>
[[nodiscard]] bool isIntersecting(const circle<T>& circle, const vec2<T>& point)
{
  return circle.radius >= distance2D(point, circle.center);
}

//====Capsule====//

template<typename T>
bool isIntersecting(const aacapsule2D<T>& a, const vec2<T>& b)
{
  return a.circleA.isIntersecting(b) || a.circleB.isIntersecting(b) || a.rect.isIntersecting(b);
}

template<typename T>
bool isIntersecting(const aacapsule2D<T>& a, const circle<T>& b)
{
  return a.circleA.isIntersecting(b) || a.circleB.isIntersecting(b) || a.rect.isIntersecting(b);
}

template<typename T>
bool isIntersecting(const aacapsule2D<T> a, const aabb2D<T>& b)
{
  return a.circleA.isIntersecting(b) || a.circleB.isIntersecting(b) || a.rect.isIntersecting(b);
}

template<typename T>
bool isIntersecting(const aacapsule2D<T>& a, const aacapsule2D<T>& b)
{
  return
    a.circleA.isIntersecting(b.circleA) || a.circleB.isIntersecting(b.circleB) ||
    a.rect.isIntersecting(b.rect) || a.circleA.isIntersecting(b.circleB) ||
    a.rect.isIntersecting(b.circleA) || a.rect.isIntersecting(b.circleB) ||
    b.rect.isIntersecting(a.circleA) || b.rect.isIntersecting(a.circleB);
}

//====Sphere====//

/// Sphere/sphere intersection test
template<typename T>
[[nodiscard]] bool isIntersecting(const sphere<T>& a, const sphere<T>& b)
{
  return a.radius + b.radius >= distance3D(a.center, b.center);
}

//====Line segment====//

/// Line segment/line segment intersection
/*template <typename T>
[[nodiscard]] bool isIntersecting(const linesegment2D<T>& a, const linesegment2D<T>& b, vec2<T>& out)
{
  T x1 = a.point1.x(), x2 = a.point2.x(), x3 = b.point1.x(), x4 = b.point2.x();
  T y1 = a.point1.y(), y2 = a.point2.y(), y3 = b.point1.y(), y4 = b.point2.y();
  T pre = (x1 * y2 - y1 * x2), post = (x3 * y4 - y3 * x4);
  T det = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
  
  if(det == 0)
  {
    return false;
  }
  
  T x = (pre * (x3 - x4) - (x1 - x2) * post) / det;
  T y = (pre * (y3 - y4) - (y1 - y2) * post) / det;
  
  if(x < std::min(x1, x2) || x > std::max(x1, x2) || x < std::min(x3, x4) || x > std::max(x3, x4))
  {
    return false;
  }
  
  if(y < std::min(y1, y2) || y > std::max(y1, y2) || y < std::min(y3, y4) || y > std::max(y3, y4))
  {
    return false;
  }
  
  out = {x, y};
  return true;
}*/

/// Line segmennt/line segment intersection
template<typename T>
[[nodiscard]] bool isIntersecting(const linesegment2D<T>& a, const linesegment2D<T>& b, vec2<T>& out)
{
  float s1_x = a.point2.x() - a.point1.x();
  const float s1_y = a.point2.y() - a.point1.y();
  float s2_x = b.point2.x() - b.point1.x();
  float s2_y = b.point2.y() - b.point1.y();

  const float s = (-s1_y * (a.point1.x() - b.point1.x()) + s1_x * (a.point1.y() - b.point1.y())) / (-s2_x * s1_y + s1_x * s2_y);
  const float t = (s2_x * (a.point1.y() - b.point1.y()) - s2_y * (a.point1.x() - b.point1.x())) / (-s2_x * s1_y + s1_x * s2_y);

  if(s >= 0 && s <= 1 && t >= 0 && t <= 1)
  {
    out.x() = a.point1.x() + (t * s1_x);
    out.y() = a.point1.y() + (t * s1_y);
    return true;
  }
  return false;
}
