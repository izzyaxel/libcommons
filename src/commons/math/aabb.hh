#pragma once

#include "vec2.hh"

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

  T minX, maxX, minY, maxY, centerX, centerY;
};

/// 3-dimensional axis aligned bounding box
template<typename T>
struct aabb3D //TODO mirror 2D version's functions
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

  T minX, maxX, minY, maxY, minZ, maxZ, centerX, centerY, centerZ;
};
