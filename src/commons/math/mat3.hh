#pragma once

#include <ctgmath>
#include <cstring>

template <typename T>
struct vec3;

template <typename T>
struct mat4x4;

template <typename T>
struct mat3x3
{
  /// X Y Z W on each row, init to identity, row dominant
  T data[3][3]{
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
  };

  constexpr mat3x3() = default;

  template <typename U>
  constexpr explicit mat3x3(const mat3x3<U>& in)
  {
    this->data[0][0] = in[0][0];
    this->data[0][1] = in[0][1];
    this->data[0][2] = in[0][2];
    this->data[1][0] = in[1][0];
    this->data[1][1] = in[1][1];
    this->data[1][2] = in[1][2];
    this->data[2][0] = in[2][0];
    this->data[2][1] = in[2][1];
    this->data[2][2] = in[2][2];
  }

  constexpr explicit mat3x3(const mat4x4<T>& in)
  {
    this->data[0][0] = in[0][0];
    this->data[0][1] = in[0][1];
    this->data[0][2] = in[0][2];
    this->data[1][0] = in[1][0];
    this->data[1][1] = in[1][1];
    this->data[1][2] = in[1][2];
    this->data[2][0] = in[2][0];
    this->data[2][1] = in[2][1];
    this->data[2][2] = in[2][2];
  }

  /// Subscript operators
  T* operator[](const size_t index)
  {
    return this->data[index];
  }

  T const* operator[](const size_t index) const
  {
    return this->data[index];
  }

  /// Compare equality with another 3x3 matrix
  bool operator==(const mat3x3& other) const
  {
    return this->data[0][0] == other[0][0] && this->data[1][0] == other[1][0] && this->data[2][0] == other[2][0] &&
           this->data[0][1] == other[0][1] && this->data[1][1] == other[1][1] && this->data[2][1] == other[2][1] &&
           this->data[0][2] == other[0][2] && this->data[1][2] == other[1][2] && this->data[2][2] == other[2][2];
  }

  /// Compare inequality with another 3x3 matrix
  bool operator!=(const mat3x3& other) const
  {
    return this->data[0][0] != other[0][0] || this->data[1][0] != other[1][0] || this->data[2][0] != other[2][0] ||
           this->data[0][1] != other[0][1] || this->data[1][1] != other[1][1] || this->data[2][1] != other[2][1] ||
           this->data[0][2] != other[0][2] || this->data[1][2] != other[1][2] || this->data[2][2] != other[2][2];
  }

  /// Multiply this 3x3 matrix by another
  mat3x3 operator*(const mat3x3& other) const
  {
    mat4x4<T> out;
    out[0][0] = this->data[0][0] * other[0][0] + this->data[0][1] * other[1][0] + this->data[0][2] * other[2][0];
    out[0][1] = this->data[0][0] * other[0][1] + this->data[0][1] * other[1][1] + this->data[0][2] * other[2][1];
    out[0][2] = this->data[0][0] * other[0][2] + this->data[0][1] * other[1][2] + this->data[0][2] * other[2][2];
    out[1][0] = this->data[1][0] * other[0][0] + this->data[1][1] * other[1][0] + this->data[1][2] * other[2][0];
    out[1][1] = this->data[1][0] * other[0][1] + this->data[1][1] * other[1][1] + this->data[1][2] * other[2][1];
    out[1][2] = this->data[1][0] * other[0][2] + this->data[1][1] * other[1][2] + this->data[1][2] * other[2][2];
    out[2][0] = this->data[2][0] * other[0][0] + this->data[2][1] * other[1][0] + this->data[2][2] * other[2][0];
    out[2][1] = this->data[2][0] * other[0][1] + this->data[2][1] * other[1][1] + this->data[2][2] * other[2][1];
    out[2][2] = this->data[2][0] * other[0][2] + this->data[2][1] * other[1][2] + this->data[2][2] * other[2][2];
    return out;
  }

  /// Get the determinant of this 3x3 matrix
  [[nodiscard]] T determinant() const
  {
    return
      this->data[0][0] * this->data[1][1] * this->data[2][2] -
      this->data[0][0] * this->data[1][2] * this->data[2][1] +
      this->data[0][1] * this->data[1][0] * this->data[2][2] +
      this->data[0][1] * this->data[1][2] * this->data[2][1] +
      this->data[0][2] * this->data[1][0] * this->data[2][1] -
      this->data[0][2] * this->data[1][1] * this->data[2][0];
  }

  /// Get a compound scaled 4x4 matrix from this matrix and a 3-dimensional vector
  [[nodiscard]] mat3x3 compoundScale(const vec3<T>& scaleVec) const
  {
    mat3x3 out;
    out[0][0] = this->data[0][0] * scaleVec[0];
    out[0][1] = this->data[0][1] * scaleVec[0];
    out[0][2] = this->data[0][2] * scaleVec[0];
    out[1][0] = this->data[1][0] * scaleVec[1];
    out[1][1] = this->data[1][1] * scaleVec[1];
    out[1][2] = this->data[1][2] * scaleVec[1];
    out[2][0] = this->data[2][0] * scaleVec[2];
    out[2][1] = this->data[2][1] * scaleVec[2];
    out[2][2] = this->data[2][2] * scaleVec[2];
    return out;
  }

  [[nodiscard]] mat3x3 compoundScale(const T& scalar) const
  {
    mat3x3 out;
    out[0][0] = this->data[0][0] * scalar;
    out[0][1] = this->data[0][1] * scalar;
    out[0][2] = this->data[0][2] * scalar;
    out[1][0] = this->data[1][0] * scalar;
    out[1][1] = this->data[1][1] * scalar;
    out[1][2] = this->data[1][2] * scalar;
    out[2][0] = this->data[2][0] * scalar;
    out[2][1] = this->data[2][1] * scalar;
    out[2][2] = this->data[2][2] * scalar;
    return out;
  }

  /// Get an inverted 3x3 matrix based on this one
  [[nodiscard]] mat3x3 invert() const
  {
    mat3x3 out;

    out.data[0][0] = this->data[1][1] * this->data[2][2] - this->data[1][2] * this->data[2][1];
    out.data[0][1] = this->data[0][2] * this->data[2][1] - this->data[0][1] * this->data[2][2];
    out.data[0][2] = this->data[0][1] * this->data[1][2] - this->data[0][2] * this->data[1][1];
    out.data[1][0] = this->data[1][2] * this->data[2][0] - this->data[1][0] * this->data[2][2];
    out.data[1][1] = this->data[0][0] * this->data[2][2] - this->data[0][2] * this->data[2][0];
    out.data[1][2] = this->data[0][2] * this->data[1][0] - this->data[0][0] * this->data[1][2];
    out.data[2][0] = this->data[1][0] * this->data[2][1] - this->data[1][1] * this->data[2][0];
    out.data[2][1] = this->data[0][1] * this->data[2][0] - this->data[0][0] * this->data[2][1];
    out.data[2][2] = this->data[0][0] * this->data[1][1] - this->data[0][1] * this->data[1][0];
    out = out.compoundScale((T)1 / out.determinant());
    return out;
  }

  /// Transpose this 3x3 matrix
  [[nodiscard]] mat3x3 transpose() const
  {
    mat3x3 out;
    out[0][0] = this->data[0][0];
    out[0][1] = this->data[1][0];
    out[0][2] = this->data[2][0];
    out[1][0] = this->data[0][1];
    out[1][1] = this->data[1][1];
    out[1][2] = this->data[2][1];
    out[2][0] = this->data[0][2];
    out[2][1] = this->data[1][2];
    out[2][2] = this->data[2][2];
    return out;
  }

  [[nodiscard]] static size_t size()
  {
    return 9;
  }

  /// Compose a string out of this mat4x4's values
  [[nodiscard]] std::string toString() const
  {
    std::string out = "(mat3x3)\n";
    for(int i = 0; i < 3; i++)
    {
      out += "[";
      for(int j = 0; j < 3; j++)
      {
        switch(j)
        {
          case 0:
            out += "x: ";
            break;
          case 1:
            out += "y: ";
            break;
          case 2:
            out += "z: ";
            break;
          default:
            break;
        }
        out += std::to_string(this->data[i][j]);
        if(j < 2) out += " ";
      }
      out += "]\n";
    }
    return out;
  }

  /// Print this mat4x4 with printf
  void print(const std::string& name) const
  {
    printf("%s: %s\n", name.data(), this->toString().data());
  }
};
