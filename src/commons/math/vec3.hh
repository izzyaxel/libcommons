#pragma once

#include "vec2.hh"

#include <string>

template <typename T>
struct vec4;

template <typename T>
struct quat;

template <typename T>
struct vec3
{
  /// X Y Z
  T data[3];

  /// Get a reference to one of the contained values

  [[nodiscard]] T& x() { return this->data[0]; }

  [[nodiscard]] T& y() { return this->data[1]; }

  [[nodiscard]] T& z() { return this->data[2]; }

  [[nodiscard]] const T& x() const { return this->data[0]; }

  [[nodiscard]] const T& y() const { return this->data[1]; }

  [[nodiscard]] const T& z() const { return this->data[2]; }

  [[nodiscard]] T& r() { return this->data[0]; }

  [[nodiscard]] T& g() { return this->data[1]; }

  [[nodiscard]] T& b() { return this->data[2]; }

  [[nodiscard]] const T& r() const { return this->data[0]; }

  [[nodiscard]] const T& g() const { return this->data[1]; }

  [[nodiscard]] const T& b() const { return this->data[2]; }

  // 3-way Swizzling (sort of), 26 permutations (excluded xyz)

  [[nodiscard]] vec3 xxx() const { return vec3{this->data[0]}; }

  [[nodiscard]] vec3 yyy() const { return vec3{this->data[1]}; }

  [[nodiscard]] vec3 zzz() const { return vec3{this->data[2]}; }

  [[nodiscard]] vec3 zyx() const { return vec3{this->data[2], this->data[1], this->data[0]}; }

  [[nodiscard]] vec3 xxy() const { return vec3{this->data[0], this->data[0], this->data[1]}; }

  [[nodiscard]] vec3 xxz() const { return vec3{this->data[0], this->data[0], this->data[2]}; }

  [[nodiscard]] vec3 yyx() const { return vec3{this->data[1], this->data[1], this->data[0]}; }

  [[nodiscard]] vec3 yyz() const { return vec3{this->data[0], this->data[1], this->data[2]}; }

  [[nodiscard]] vec3 zzx() const { return vec3{this->data[2], this->data[2], this->data[0]}; }

  [[nodiscard]] vec3 zzy() const { return vec3{this->data[2], this->data[2], this->data[1]}; }

  [[nodiscard]] vec3 xyy() const { return vec3{this->data[0], this->data[1], this->data[1]}; }

  [[nodiscard]] vec3 xzz() const { return vec3{this->data[0], this->data[2], this->data[2]}; }

  [[nodiscard]] vec3 yxx() const { return vec3{this->data[1], this->data[0], this->data[0]}; }

  [[nodiscard]] vec3 yzz() const { return vec3{this->data[1], this->data[2], this->data[2]}; }

  [[nodiscard]] vec3 zxx() const { return vec3{this->data[2], this->data[0], this->data[0]}; }

  [[nodiscard]] vec3 zyy() const { return vec3{this->data[2], this->data[1], this->data[1]}; }

  [[nodiscard]] vec3 xyx() const { return vec3{this->data[0], this->data[1], this->data[0]}; }

  [[nodiscard]] vec3 xzx() const { return vec3{this->data[0], this->data[2], this->data[0]}; }

  [[nodiscard]] vec3 yxy() const { return vec3{this->data[1], this->data[0], this->data[1]}; }

  [[nodiscard]] vec3 yzy() const { return vec3{this->data[1], this->data[2], this->data[1]}; }

  [[nodiscard]] vec3 zxz() const { return vec3{this->data[2], this->data[0], this->data[2]}; }

  [[nodiscard]] vec3 zyz() const { return vec3{this->data[2], this->data[1], this->data[2]}; }

  [[nodiscard]] vec3 xzy() const { return vec3{this->data[0], this->data[2], this->data[1]}; }

  [[nodiscard]] vec3 yzx() const { return vec3{this->data[1], this->data[2], this->data[0]}; }

  [[nodiscard]] vec3 zxy() const { return vec3{this->data[2], this->data[0], this->data[1]}; }

  [[nodiscard]] vec3 yxz() const { return vec3{this->data[1], this->data[0], this->data[2]}; }

  [[nodiscard]] vec3 rrr() const { return vec3{this->data[0]}; }

  [[nodiscard]] vec3 ggg() const { return vec3{this->data[1]}; }

  [[nodiscard]] vec3 bbb() const { return vec3{this->data[2]}; }

  [[nodiscard]] vec3 bgr() const { return vec3{this->data[2], this->data[1], this->data[0]}; }

  [[nodiscard]] vec3 rrg() const { return vec3{this->data[0], this->data[0], this->data[1]}; }

  [[nodiscard]] vec3 rrb() const { return vec3{this->data[0], this->data[0], this->data[2]}; }

  [[nodiscard]] vec3 ggr() const { return vec3{this->data[1], this->data[1], this->data[0]}; }

  [[nodiscard]] vec3 ggb() const { return vec3{this->data[0], this->data[1], this->data[2]}; }

  [[nodiscard]] vec3 bbr() const { return vec3{this->data[2], this->data[2], this->data[0]}; }

  [[nodiscard]] vec3 bbg() const { return vec3{this->data[2], this->data[2], this->data[1]}; }

  [[nodiscard]] vec3 rgg() const { return vec3{this->data[0], this->data[1], this->data[1]}; }

  [[nodiscard]] vec3 rbb() const { return vec3{this->data[0], this->data[2], this->data[2]}; }

  [[nodiscard]] vec3 grr() const { return vec3{this->data[1], this->data[0], this->data[0]}; }

  [[nodiscard]] vec3 gbb() const { return vec3{this->data[1], this->data[2], this->data[2]}; }

  [[nodiscard]] vec3 brr() const { return vec3{this->data[2], this->data[0], this->data[0]}; }

  [[nodiscard]] vec3 bgg() const { return vec3{this->data[2], this->data[1], this->data[1]}; }

  [[nodiscard]] vec3 rgr() const { return vec3{this->data[0], this->data[1], this->data[0]}; }

  [[nodiscard]] vec3 rbr() const { return vec3{this->data[0], this->data[2], this->data[0]}; }

  [[nodiscard]] vec3 grg() const { return vec3{this->data[1], this->data[0], this->data[1]}; }

  [[nodiscard]] vec3 gbg() const { return vec3{this->data[1], this->data[2], this->data[1]}; }

  [[nodiscard]] vec3 brb() const { return vec3{this->data[2], this->data[0], this->data[2]}; }

  [[nodiscard]] vec3 bgb() const { return vec3{this->data[2], this->data[1], this->data[2]}; }

  [[nodiscard]] vec3 rbg() const { return vec3{this->data[0], this->data[2], this->data[1]}; }

  [[nodiscard]] vec3 gbr() const { return vec3{this->data[1], this->data[2], this->data[0]}; }

  [[nodiscard]] vec3 brg() const { return vec3{this->data[2], this->data[0], this->data[1]}; }

  [[nodiscard]] vec3 grb() const { return vec3{this->data[1], this->data[0], this->data[2]}; }

  // 2-way Swizzling (sort of), 9 permutations

  [[nodiscard]] vec2<T> xx() const { return vec2<T>{this->data[0], this->data[0]}; }

  [[nodiscard]] vec2<T> xy() const { return vec2<T>{this->data[0], this->data[1]}; }

  [[nodiscard]] vec2<T> xz() const { return vec2<T>{this->data[0], this->data[2]}; }

  [[nodiscard]] vec2<T> yy() const { return vec2<T>{this->data[1], this->data[1]}; }

  [[nodiscard]] vec2<T> yx() const { return vec2<T>{this->data[1], this->data[0]}; }

  [[nodiscard]] vec2<T> yz() const { return vec2<T>{this->data[1], this->data[2]}; }

  [[nodiscard]] vec2<T> zz() const { return vec2<T>{this->data[2], this->data[2]}; }

  [[nodiscard]] vec2<T> zx() const { return vec2<T>{this->data[2], this->data[0]}; }

  [[nodiscard]] vec2<T> zy() const { return vec2<T>{this->data[2], this->data[1]}; }

  constexpr vec3() = default;

  template <typename U>
  constexpr explicit vec3(const vec3<U>& other)
  {
    this->data[0] = other.data[0];
    this->data[1] = other.data[1];
    this->data[2] = other.data[2];
  }

  /// Construct a v3 out of 3 values
  constexpr vec3(const T x, const T y, const T z)
  {
    this->data[0] = x;
    this->data[1] = y;
    this->data[2] = z;
  }

  constexpr explicit vec3(const T scalar)
  {
    this->data[0] = scalar;
    this->data[1] = scalar;
    this->data[2] = scalar;
  }

  constexpr vec3(const vec2<T>& first, const T & second)
  {
    this->data[0] = first.x();
    this->data[1] = first.y();
    this->data[2] = second;
  }

  /// Truncate a v4 to a v3
  constexpr explicit vec3(const vec4<T>& trunc)
  {
    this->data[0] = trunc.x();
    this->data[1] = trunc.y();
    this->data[2] = trunc.z();
  }

  /// Subscript operator
  T& operator[](const size_t index)
  {
    return this->data[index];
  }

  T const& operator[](const size_t index) const
  {
    return this->data[index];
  }

  /// Compare equality with another v3
  bool operator==(const vec3& other) const
  {
    return this->data[0] == other[0] && this->data[1] == other[1] && this->data[2] == other[2];
  }

  /// Compare inequality with another v3
  bool operator!=(const vec3& other) const
  {
    return this->data[0] != other[0] || this->data[1] != other[1] || this->data[2] != other[2];
  }

  /// Add this v3 to another
  vec3 operator+(const vec3& other) const
  {
    return vec3{this->data[0] + other[0], this->data[1] + other[1], this->data[2] + other[2]};
  }

  /// Add a scalar number to this v3
  vec3 operator+(T const &scalar) const
  {
    return vec3{(T)(this->data[0] + scalar), (T)(this->data[1] + scalar), (T)(this->data[2] + scalar)};
  }

  /// Subtract this v3 from another
  vec3 operator-(const vec3& other) const
  {
    return vec3{this->data[0] - other[0], this->data[1] - other[1], this->data[2] - other[2]};
  }

  /// Subtract a scalar number from this v3
  vec3 operator-(const T scalar) const
  {
    return vec3{(T)(this->data[0] - scalar), (T)(this->data[1] - scalar), (T)(this->data[2] - scalar)};
  }

  /// Negate this v3
  vec3 operator-() const
  {
    return vec3{-this->data[0], -this->data[1], -this->data[2]};
  }

  /// Multiply this v3 with another
  vec3 operator*(const vec3& other) const
  {
    return vec3{this->data[0] * other[0], this->data[1] * other[1], this->data[2] * other[2]};
  }

  /// Multiply this v3 by a scalar number
  vec3 operator*(const T scalar) const
  {
    return vec3{(T)(this->data[0] * scalar), (T)(this->data[1] * scalar), (T)(this->data[2] * scalar)};
  }

  vec3 operator*(const quat<T>& in)
  {
    vec3 q{in[0], in[1], in[2]};
    vec3 w1 = this->cross(q) * (T)(2);
    return *this + w1 * in[3] + w1.cross(q);
  }

  /// Divide this v3 by another
  vec3 operator/(const vec3& other) const
  {
    return vec3{this->data[0] / other[0], this->data[1] / other[1], this->data[2] / other[2]};
  }

  /// Divide this v3 by a scalar number
  vec3 operator/(const T scalar) const
  {
    return vec3{(T)(this->data[0] / scalar), (T)(this->data[1] / scalar), (T)(this->data[2] / scalar)};
  }

  /// Compound add this v3 to another
  vec3 operator+=(const vec3& other)
  {
    this->data[0] += other[0];
    this->data[1] += other[1];
    this->data[2] += other[2];
    return *this;
  }

  /// Compound subtract this v3 from another
  vec3 operator-=(const vec3& other)
  {
    this->data[0] -= other[0];
    this->data[1] -= other[1];
    this->data[2] -= other[2];
    return *this;
  }

  /// Compound multiply this v3 with another
  vec3 operator*=(const vec3& other)
  {
    this->data[0] *= other[0];
    this->data[1] *= other[1];
    this->data[2] *= other[2];
    return *this;
  }

  /// Compound divide this v3 by another
  vec3 operator/=(const vec3& other)
  {
    this->data[0] /= other[0];
    this->data[1] /= other[1];
    this->data[2] /= other[2];
    return *this;
  }

  /// Increment all values in this v3 (prefix)
  vec3& operator++()
  {
    (void)this->data[0]++;
    (void)this->data[1]++;
    (void)this->data[2]++;
    return *this;
  }

  /// Increment all values in this v3 (postfix)
  vec3 operator++(int)
  {
    vec3 out = *this;
    (void)this->data[0]++;
    (void)this->data[1]++;
    (void)this->data[2]++;
    return out;
  }

  /// Decrement all values in this v3 (prefix)
  vec3& operator--()
  {
    (void)this->data[0]--;
    (void)this->data[1]--;
    (void)this->data[2]--;
    return *this;
  }

  /// Decrement all values in this v3 (postfix)
  vec3 operator--(int)
  {
    vec3 out = *this;
    (void)this->data[0]--;
    (void)this->data[1]--;
    (void)this->data[2]--;
    return out;
  }

  /// Set all values individually
  void set(const T x, const T y, const T z)
  {
    this->data[0] = x;
    this->data[1] = y;
    this->data[2] = z;
  }

  /// Set all values to one given value
  void setAll(const T value)
  {
    this->set(value, value, value);
  }

  void floor()
  {
    this->data[0] = (T)std::floor(this->data[0]);
    this->data[1] = (T)std::floor(this->data[1]);
    this->data[2] = (T)std::floor(this->data[2]);
  }

  void ceil()
  {
    this->data[0] = (T)std::ceil(this->data[0]);
    this->data[1] = (T)std::ceil(this->data[1]);
    this->data[2] = (T)std::ceil(this->data[2]);
  }

  void round()
  {
    this->data[0] = (T)std::round(this->data[0]);
    this->data[1] = (T)std::round(this->data[1]);
    this->data[2] = (T)std::round(this->data[2]);
  }

  /// Invert sign on all values
  void invert()
  {
    this->data[0] = -this->data[0];
    this->data[1] = -this->data[1];
    this->data[2] = -this->data[2];
  }

  /// Get an inverted v3
  [[nodiscard]] vec3 inverse() const
  {
    return vec3{-this->data[0], -this->data[1], -this->data[2]};
  }

  /// Get the magnitude of this v3
  [[nodiscard]] T mag() const
  {
    return std::sqrt(this->data[0] * this->data[0] + this->data[1] * this->data[1] + this->data[2] * this->data[2]);
  }

  /// Get the dot product of this v3 and another
  [[nodiscard]] T dot(const vec3& b) const
  {
    return this->data[0] * b[0] + this->data[1] * b[1] + this->data[2] * b[2];
  }

  /// Get the cross product of this v3 and another
  [[nodiscard]] vec3 cross(const vec3& b) const
  {
    vec3 out;
    out[0] = this->data[1] * b[2] - this->data[2] * b[1];
    out[1] = this->data[2] * b[0] - this->data[0] * b[2];
    out[2] = this->data[0] * b[1] - this->data[1] * b[0];
    return out;
  }

  ///Normalize this v3
  void normalize()
  {
    T length = this->mag();
    this->data[0] /= length;
    this->data[1] /= length;
    this->data[2] /= length;
  }

  /// Get a normalized v3
  [[nodiscard]] vec3 normalized() const
  {
    vec3 out;
    T length = this->mag();
    out[0] = this->data[0] / length;
    out[1] = this->data[1] / length;
    out[2] = this->data[2] / length;
    return out;
  }

  /// Create a yaw/pitch/roll rotation from relative mouse movement values
  [[nodiscard]] static vec3 rotateFromMouseEuler(const T xrel, const T yrel, const T lookSensitivity)
  {
    vec3 out{};
    out[0] = -yrel * lookSensitivity;
    out[1] = -xrel * lookSensitivity;
    out[2] = 0;
    return out;
  }

  /// (For directional unit vectors) Check if the direction this v3 indicates is cardinal
  [[nodiscard]] bool isCardinal() const
  {
    return std::abs(this->data[0]) + std::abs(this->data[1]) + std::abs(this->data[2]) == 1;
  }

  [[nodiscard]] static size_t size()
  {
    return 3;
  }

  /// Compose a string out of this v3's values
  [[nodiscard]] std::string toString() const
  {
    std::string out = "(vec3)\n[x: ";
    out += std::to_string(this->data[0]);
    out += " y: ";
    out += std::to_string(this->data[1]);
    out += " z: ";
    out += std::to_string(this->data[2]);
    out += "]\n";
    return out;
  }

  /// Print this v3 with printf
  void print(const std::string& name) const
  {
    printf("%s: %s\n", name.data(), this->toString().data());
  }
};
