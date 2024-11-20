#pragma once

#include "vec2.hh"
#include "linesegment.hh"

template<typename T>
struct circle;

/// 2-dimensional axis aligned bounding box
template<typename T>
struct aabb2D
{
  constexpr aabb2D() = default;

  constexpr aabb2D(const T minX, const T maxX, const T minY, const T maxY) :
  minX(minX), maxX(maxX), minY(minY), maxY(maxY), centerX((maxX - minX) / (T)2), centerY((maxY - minY) / (T)2)
  {}

  constexpr aabb2D(const T minX, const T maxX, const T minY, const T maxY, const T centerX, const T centerY) :
  minX(minX), maxX(maxX), minY(minY), maxY(maxY), centerX(centerX), centerY(centerY)
  {}

  constexpr aabb2D(const vec2<T> center, const vec2<T> dimensions)
  {
    this->centerX = center.x();
    this->centerY = center.y();
    T halfX = dimensions.x() / (T)2, halfY = dimensions.y() / (T)2;
    this->minX = this->centerX - halfX;
    this->maxX = this->centerX + halfX;
    this->minY = this->centerY - halfY;
    this->maxY = this->centerY + halfY;
  }
  
  [[nodiscard]] vec2<T> center() const
  {
    return {this->centerX, this->centerY};
  }
  
  [[nodiscard]] vec2<T> upperLeft() const
  {
    return {this->minX, this->maxY};
  }

  [[nodiscard]] vec2<T> upperRight() const
  {
    return {this->maxX, this->maxY};
  }

  [[nodiscard]] vec2<T> lowerLeft() const
  {
    return {this->minX, this->minY};
  }

  [[nodiscard]] vec2<T> lowerRight() const
  {
    return {this->maxX, this->minY};
  }

  [[nodiscard]] T width() const
  {
    return this->maxX - this->minX;
  }

  [[nodiscard]] T height() const
  {
    return this->maxY - this->minY;
  }

  /// Reconstruct this AABB
  void construct(const T minX, const T maxX, const T minY, const T maxY)
  {
    this->minX = minX;
    this->maxX = maxX;
    this->minY = minY;
    this->maxY = maxY;
    this->centerX = (maxX - minX) / (T)2.0;
    this->centerY = (maxY - minY) / (T)2.0;
  }

  void offset(const T xOffset, const T yOffset)
  {
    this->minX += xOffset;
    this->maxX += xOffset;
    this->minY += yOffset;
    this->maxY += yOffset;
    this->centerX = (maxX - minX) / (T)2.0;
    this->centerY = (maxY - minY) / (T)2.0;
  }

  /// Check if this AABB contains a given point
  [[nodiscard]] bool containsPoint(const T x, const T y)
  {
    return x > this->minX && x < this->maxX && y > this->minY && y < this->maxY;
  }

  /// AABB-line segment collision
  [[nodiscard]] bool isIntersecting(const linesegment2D<T>& other, T& closestHit)
  {
    T hWidth = (this->maxX - this->minX) / (T)2, hHeight = (this->maxY - this->minY) / 2;
    linesegment2D<T> top{
                       vec2<T>{this->centerX - hWidth, this->centerY + hHeight},
                       vec2<T>{this->centerX + hWidth, this->centerY + hHeight}
                     },
                     bottom{
                       vec2<T>{this->centerX - hWidth, this->centerY - hHeight},
                       vec2<T>{this->centerX + hWidth, this->centerY - hHeight}
                     },
                     left{
                       vec2<T>{this->centerX - hWidth, this->centerY - hHeight},
                       vec2<T>{this->centerX - hWidth, this->centerY + hHeight}
                     },
                     right{
                       vec2<T>{this->centerX + hWidth, this->centerY - hHeight},
                       vec2<T>{this->centerX + hWidth, this->centerY + hHeight}
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

  /// AABB-aabb collision
  [[nodiscard]] bool isIntersecting(const aabb2D& other) const
  {
    return (this->minX < other.maxX) != (this->maxX < other.minX) && (this->minY < other.maxY) != (this->maxY < other.minY);
  }

  /// AABB-circle collision
  [[nodiscard]] bool isIntersecting(const circle<T>& other)
  {
    const aabb2D broadOther = aabb2D(other.center.x() - other.radius, other.center.x() + other.radius,other.center.y() - other.radius, other.center.y() + other.radius);
    if(!this->isIntersecting(broadOther))
    {
      return false;
    }
    
    vec2<T> ul = {this->minX, this->maxY};
    vec2<T> ur = {this->maxX, this->maxY};
    vec2<T> ll = {this->minX, this->minY};
    vec2<T> lr = {this->maxX, this->maxY};
    T distUL = std::sqrt((other.center.x() - ul.x()) * (other.center.x() - ul.x()) + (other.center.y() - ul.y()) * (other.center.y() - ul.y()));
    T distUR = std::sqrt((other.center.x() - ur.x()) * (other.center.x() - ur.x()) + (other.center.y() - ur.y()) * (other.center.y() - ur.y()));
    T distLL = std::sqrt((other.center.x() - ll.x()) * (other.center.x() - ll.x()) + (other.center.y() - ll.y()) * (other.center.y() - ll.y()));
    T distLR = std::sqrt((other.center.x() - lr.x()) * (other.center.x() - lr.x()) + (other.center.y() - lr.y()) * (other.center.y() - lr.y()));
    return distUL < other.radius || distUR < other.radius || distLR < other.radius || distLL < other.radius;
  }

  /// Predict an intersection with another AABB
  [[nodiscard]] bool predictIntersection(const T xOffset, const T yOffset, const aabb2D& other) const
  {
    return (this->minX + xOffset < other.maxX) != (this->maxX + xOffset < other.minX) && (this->minY + yOffset < other.maxY) != (this->maxY + yOffset < other.minY);
  }

  T minX, maxX, minY, maxY, centerX, centerY;
};

/// 3-dimensional axis aligned bounding box
template<typename T>
struct aabb3D
{
  constexpr aabb3D() = default;

  constexpr aabb3D(const T minX, const T maxX, const T minY, const T maxY, const T minZ, const T maxZ) :
  minX(minX), maxX(maxX), minY(minY), maxY(maxY), minZ(minZ), maxZ(maxZ),
  centerX((maxX - minX) / (T)2), centerY((maxY - minY) / (T)2), centerZ((maxZ - minZ) / (T)2)
  {}

  /// Construct/reconstruct this AABB
  void construct(const T minX, const T maxX, const T minY, const T maxY, const T minZ, const T maxZ)
  {
    this->minX = minX;
    this->maxX = maxX;
    this->minY = minY;
    this->maxY = maxY;
    this->minZ = minZ;
    this->maxZ = maxZ;
    this->centerX = (maxX - minX) / (T)2;
    this->centerY = (maxY - minY) / (T)2;
    this->centerZ = (maxZ - minZ) / (T)2;
  }

  /// Check if this AABB contains a given point
  [[nodiscard]] bool containsPoint(const T x, const T y, const T z)
  {
    return x > this->minX && x < this->maxX && y > this->minY && y < this->maxY && z > this->minZ && z < this->maxZ;
  }

  /// Check if this AABB is intersecting with another
  [[nodiscard]] bool isIntersecting(const aabb3D<T>& other)
  {
    return (this->minX < other.maxX) != (this->maxX < other.minX) && (this->minY < other.maxY) != (this->maxY < other.
      minY) && (this->minZ < other.maxZ) != (this->maxZ < other.minZ);
  }

  /// Predict an intersection with another AABB
  [[nodiscard]] bool predictIntersection(const T xOffset, const T yOffset, const T zOffset, const aabb3D<T>& other) const
  {
    return (this->minX + xOffset < other.maxX) != (this->maxX + xOffset < other.minX) && (this->minY + yOffset < other.maxY) != (this->maxY + yOffset < other.minY) && (this->minZ + zOffset < other.maxZ) != (this->maxZ + zOffset < other.minZ);
  }

  T minX, maxX, minY, maxY, minZ, maxZ, centerX, centerY, centerZ;
};
