#pragma once

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
