#pragma once

#include <ctgmath>
#include <limits>

/// Uses an int64_t for the base and a float or double offset from the base to minimize rounding errors
template <typename T>
struct Compound
{
  int64_t base = 0;
  T offset = 0;

  /// Specialization conversion constructor
  template <typename U>
  explicit Compound<T>(const Compound<U>& other)
  {
    this->base = other.base;
    this->offset = other.offset;
  }

  explicit Compound(T in)
  {
    this->base = (int64_t)std::floor(in);
    this->offset = in - this->base;
  }

  bool operator ==(const Compound<T>& other) const
  {
    return this->base == other.base && this->offset - other.offset < std::numeric_limits<T>::epsilon();
  }

  /// Compare inequality with another mat4x4
  bool operator !=(const Compound<T>& other) const
  {
    return this->base != other.base || this->offset - other.offset > std::numeric_limits<T>::epsilon();
  }

  Compound<T>(const Compound<T>& other)
  {
    this->base = other.base;
    this->offset = other.offset;
  }

  Compound<T>& operator =(const Compound<T>& other)
  {
    this->base = other.base;
    this->offset = other.offset;
    return *this;
  }

  Compound<T> operator +(const Compound<T>& other) const
  {
    Compound<T> out;
    out.base = this->base + other.base;
    out.offset = this->offset + other.offset;
    return out;
  }

  Compound<T> operator -(const Compound<T>& other) const
  {
    Compound<T> out;
    out.base = this->base - other.base;
    out.offset = this->offset - other.offset;
    return out;
  }

  Compound<T> operator *(const Compound<T>& other) const
  {
    Compound<T> out;
    out.base = this->base * other.base;
    out.offset = this->offset * other.offset;
    return out;
  }

  Compound<T> operator /(const Compound<T>& other) const
  {
    Compound<T> out;
    out.base = this->base / other.base;
    out.offset = this->offset / other.offset;
    return out;
  }

  Compound<T> operator +=(const Compound<T>& other) const
  {
    *this = *this + other;
    return this;
  }

  Compound<T> operator -=(const Compound<T>& other) const
  {
    *this = *this - other;
    return this;
  }

  Compound<T> operator *=(const Compound<T>& other) const
  {
    *this = *this * other;
    return this;
  }

  Compound<T> operator /=(const Compound<T>& other) const
  {
    *this = *this / other;
    return this;
  }

  /// Get the scalar value from this Compound
  [[nodiscard]] T scalar()
  {
    return (T)this->base + this->offset;
  }

  /// Get the specialized scalar value from this Compound
  template <typename U> [[nodiscard]] U scalar()
  {
    return (U)this->base + this->offset;
  }
};
