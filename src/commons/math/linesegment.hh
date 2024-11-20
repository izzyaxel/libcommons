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

  /*/// Find the point of intersection between this line and another
  [[nodiscard]] inline bool isIntersecting(const linesegment2D<T>& other, vec2<T>& out)
  {
    T x1 = this->point1.x(), x2 = this->point2.x(), x3 = other.point1.x(), x4 = other.point2.x();
    T y1 = this->point1.y(), y2 = this->point2.y(), y3 = other.point1.y(), y4 = other.point2.y();
    T pre = (x1 * y2 - y1 * x2), post = (x3 * y4 - y3 * x4);
    T det = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if(det == 0) return false;
    T x = (pre * (x3 - x4) - (x1 - x2) * post) / det;
    T y = (pre * (y3 - y4) - (y1 - y2) * post) / det;
    if(x < std::min(x1, x2) || x > std::max(x1, x2) || x < std::min(x3, x4) || x > std::max(x3, x4)) return false;
    if(y < std::min(y1, y2) || y > std::max(y1, y2) || y < std::min(y3, y4) || y > std::max(y3, y4)) return false;
    out = {x, y};
    return true;
  }*/

  [[nodiscard]] bool isIntersecting(const linesegment2D<T>& other, vec2<T>& out)
  {
    float s1_x = this->point2.x() - this->point1.x();
    const float s1_y = this->point2.y() - this->point1.y();
    float s2_x = other.point2.x() - other.point1.x();
    float s2_y = other.point2.y() - other.point1.y();

    const float s = (-s1_y * (this->point1.x() - other.point1.x()) + s1_x * (this->point1.y() - other.point1.y())) / (-s2_x * s1_y + s1_x * s2_y);
    const float t = (s2_x * (this->point1.y() - other.point1.y()) - s2_y * (this->point1.x() - other.point1.x())) / (-s2_x * s1_y + s1_x * s2_y);

    if(s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
      out.x() = this->point1.x() + (t * s1_x);
      out.y() = this->point1.y() + (t * s1_y);
      return true;
    }
    return false;
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
