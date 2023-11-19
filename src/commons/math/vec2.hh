#pragma once

#include <ctgmath>
#include <cstdint>
#include <cstring>

template <typename T> struct vec2
{
  T data[2];

  [[nodiscard]] T& x()
  {
    return this->data[0];
  }

  [[nodiscard]] T& y()
  {
    return this->data[1];
  }

  [[nodiscard]] T const& x() const
  {
    return this->data[0];
  }

  [[nodiscard]] T const& y() const
  {
    return this->data[1];
  }

  [[nodiscard]] T& width()
  {
    return this->x();
  }

  [[nodiscard]] T& height()
  {
    return this->y();
  }

  [[nodiscard]] T const& width() const
  {
    return this->x();
  }

  [[nodiscard]] T const& height() const
  {
    return this->y();
  }

  // 2-way Swizzling (sort of) 3 permutations
  [[nodiscard]] vec2<T> xx() const { return vec2<T>{this->data[0], this->data[0]}; }

  [[nodiscard]] vec2<T> yy() const { return vec2<T>{this->data[1], this->data[1]}; }

  [[nodiscard]] vec2<T> yx() const { return vec2<T>{this->data[1], this->data[0]}; }

  constexpr vec2<T>() = default;

  template <typename U> constexpr explicit vec2<T>(vec2<U> const& other)
  {
    this->data[0] = other.data[0];
    this->data[1] = other.data[1];
  }

  constexpr vec2<T>(T x, T y)
  {
    this->data[0] = x;
    this->data[1] = y;
  }

  constexpr explicit vec2<T>(T const& scalar)
  {
    this->data[0] = scalar;
    this->data[1] = scalar;
  }

  T& operator[](size_t index)
  {
    return this->data[index];
  }

  T const& operator[](size_t index) const
  {
    return this->data[index];
  }

  bool operator==(vec2<T> const& other) const
  {
    return this->data[0] == other[0] && this->data[1] == other[1];
  }

  bool operator!=(vec2<T> const& other) const
  {
    return this->data[0] != other[0] || this->data[1] != other[1];
  }

  vec2<T> operator+(vec2<T> const& other) const
  {
    return vec2<T>{this->data[0] + other[0], this->data[1] + other[1]};
  }

  vec2<T> operator+(T const& scalar) const
  {
    return vec2<T>{(T)(this->data[0] + scalar), (T)(this->data[1] + scalar)};
  }

  vec2<T> operator-(vec2<T> const& other) const
  {
    return vec2<T>{this->data[0] - other[0], this->data[1] - other[1]};
  }

  vec2<T> operator-(T const& scalar) const
  {
    return vec2<T>{(T)(this->data[0] - scalar), (T)(this->data[1] - scalar)};
  }

  vec2<T> operator-() const
  {
    return vec2<T>{-this->data[0], -this->data[1]};
  }

  vec2<T> operator*(vec2<T> const& other) const
  {
    return vec2<T>{this->data[0] * other[0], this->data[1] * other[1]};
  }

  vec2<T> operator*(T scalar) const
  {
    return vec2<T>{(T)(this->data[0] * scalar), (T)(this->data[1] * scalar)};
  }

  vec2<T> operator/(vec2<T> const& other) const
  {
    return vec2<T>{this->data[0] / other[0], this->data[1] / other[1]};
  }

  vec2<T> operator/(T const& scalar) const
  {
    return vec2<T>{(T)(this->data[0] / scalar), (T)(this->data[1] / scalar)};
  }

  vec2<T>& operator+=(vec2<T> const& other)
  {
    this->data[0] += other[0];
    this->data[1] += other[1];
    return *this;
  }

  vec2<T>& operator-=(vec2<T> const& other)
  {
    this->data[0] -= other[0];
    this->data[1] -= other[1];
    return *this;
  }

  vec2<T>& operator*=(vec2<T> const& other)
  {
    this->data[0] *= other[0];
    this->data[1] *= other[1];
    return *this;
  }

  vec2<T>& operator/=(vec2<T> const& other)
  {
    this->data[0] /= other[0];
    this->data[1] /= other[1];
    return *this;
  }

  vec2<T>& operator++()
  {
    this->data[0]++;
    this->data[1]++;
    return *this;
  }

  vec2<T> const operator++(int)
  {
    vec2<T> out = *this;
    (void)this->data[0]++;
    (void)this->data[1]++;
    return out;
  }

  vec2<T>& operator--()
  {
    (void)this->data[0]--;
    (void)this->data[1]--;
    return *this;
  }

  vec2<T> const operator--(int)
  {
    vec2<T> out = *this;
    (void)this->data[0]--;
    (void)this->data[1]--;
    return out;
  }

  void set(T x, T y)
  {
    this->data[0] = x;
    this->data[1] = y;
  }

  void setAll(T value)
  {
    this->set(value, value);
  }

  void floor()
  {
    this->data[0] = (T)std::floor(this->data[0]);
    this->data[1] = (T)std::floor(this->data[1]);
  }

  void ceil()
  {
    this->data[0] = (T)std::ceil(this->data[0]);
    this->data[1] = (T)std::ceil(this->data[1]);
  }

  void round()
  {
    this->data[0] = (T)std::round(this->data[0]);
    this->data[1] = (T)std::round(this->data[1]);
  }

  void invert()
  {
    this->data[0] = -this->data[0];
    this->data[1] = -this->data[1];
  }

  [[nodiscard]] vec2<T> inverse() const
  {
    return {-this->data[0], -this->data[1]};
  }

  [[nodiscard]] T mag() const
  {
    return std::sqrt(this->data[0] * this->data[0] + this->data[1] * this->data[1]);
  }

  [[nodiscard]] T dot(vec2<T> const& b) const
  {
    return this->data[0] * b.x + this->data[1] * b.y;
  }

  void normalize()
  {
    T length = this->mag();
    this->data[0] /= length;
    this->data[1] /= length;
  }

  [[nodiscard]] vec2<T> normalized() const
  {
    vec2<T> out;
    T length = this->mag();
    out[0] = this->data[0] / length;
    out[1] = this->data[1] / length;
    return out;
  }

  using value_type = T;

  [[nodiscard]] size_t size() const
  {
    return 2;
  }

  [[nodiscard]] std::string toString() const
  {
    std::string out = "(vec2)\n[x: ";
    out += std::to_string(this->data[0]);
    out += " y: ";
    out += std::to_string(this->data[1]);
    out += "]\n";
    return out;
  }

  void print(std::string const& name) const
  {
    printf("%s: %s\n", name.data(), this->toString().data());
  }
};

static_assert(std::is_standard_layout<vec2<int32_t>>() && std::is_trivial<vec2<int32_t>>());
