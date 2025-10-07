#pragma once

#include "vec4.hh"
#include "general.hh"

template <typename T>
struct mat4x4;

template <typename T>
struct quat
{
  /// X Y Z W, init to identity
  T data[4]{0, 0, 0, 1};

  /// Get a reference to one of the contained values
  [[nodiscard]] T& x()
  {
    return this->data[0];
  }

  [[nodiscard]] T& y()
  {
    return this->data[1];
  }

  [[nodiscard]] T& z()
  {
    return this->data[2];
  }

  [[nodiscard]] T& w()
  {
    return this->data[3];
  }

  [[nodiscard]] T const& x() const
  {
    return this->data[0];
  }

  [[nodiscard]] T const& y() const
  {
    return this->data[1];
  }

  [[nodiscard]] T const& z() const
  {
    return this->data[2];
  }

  [[nodiscard]] T const& w() const
  {
    return this->data[3];
  }

  constexpr quat() = default;

  template <typename Q> constexpr explicit quat(const quat<Q>& other)
  {
    this->data[0] = other[0];
    this->data[1] = other[1];
    this->data[2] = other[2];
    this->data[3] = other[3];
  }

  /// Construct a quaternion out of given values
  constexpr quat(const T xIn, const T yIn, const T zIn, const T wIn)
  {
    this->data[0] = xIn;
    this->data[1] = yIn;
    this->data[2] = zIn;
    this->data[3] = wIn;
  }

  /// Convert a 4x4 matrix to a quaternion (this discards all non-rotation/orientation data)
  constexpr explicit quat(const mat4x4<T>& in)
  {
    T trace = in[0][0] + in[1][1] + in[2][2];
    if(trace > 0)
    {
      T root = (T)2 * std::sqrt(trace + (T)1);
      this->data[0] = (in[2][1] - in[1][2]) / root;
      this->data[1] = (in[0][2] - in[2][0]) / root;
      this->data[2] = (in[1][0] - in[0][1]) / root;
      this->data[3] = root / (T)4;
    }
    else if(in[0][0] > in[1][1] && in[0][0] > in[2][2])
    {
      T root = (T)2 * std::sqrt((T)1 + in[0][0] - in[1][1] - in[2][2]);
      this->data[0] = root / (T)4;
      this->data[1] = (in[0][1] + in[1][0]) / root;
      this->data[2] = (in[0][2] + in[2][0]) / root;
      this->data[3] = (in[2][1] - in[1][2]) / root;
    }
    else if(in[1][1] > in[2][2])
    {
      T root = (T)2 * std::sqrt((T)1 + in[1][1] - in[0][0] - in[2][2]);
      this->data[0] = (in[0][1] + in[1][0]) / root;
      this->data[1] = root / (T)4;
      this->data[2] = (in[1][2] + in[2][1]) / root;
      this->data[3] = (in[0][2] - in[2][0]) / root;
    }
    else
    {
      T root = (T)2 * std::sqrt((T)1 + in[2][2] - in[0][0] - in[1][1]);
      this->data[0] = (in[0][2] + in[2][0]) / root;
      this->data[1] = (in[1][2] + in[2][1]) / root;
      this->data[2] = root / (T)4;
      this->data[3] = (in[1][0] - in[0][1]) / root;
    }
  }

  /// Copy constructor
  /*quat(const quat& other)
  {
    memcpy(&this->data[0], &other.data[0], sizeof(other.data));
  }

  /// Copy assignment operator
  quat& operator=(const quat& other)
  {
    if(this == &other)
    {
      return *this;
    }
    memcpy(&this->data[0], &other.data[0], sizeof(other.data));
    return *this;
  }*/

  /// Subscript operators
  T& operator[](const size_t index)
  {
    return this->data[index];
  }

  T const& operator[](const size_t index) const
  {
    return this->data[index];
  }

  /// Compare equality of two quaternions
  bool operator==(const quat& other) const
  {
    return this->data[0] == other[0] && this->data[1] == other[1] && this->data[2] == other[2] && this->data[3] == other[3];
  }

  /// Compare inequality of two quaternions
  bool operator!=(const quat& other) const
  {
    return this->data[0] != other[0] || this->data[1] != other[1] || this->data[2] != other[2] || this->data[3] != other[3];
  }

  /// Multiply/compose this quaternion by/with another
  quat operator*(const quat& other) const
  {
    return quat{
      (this->data[0] * other[3] + this->data[1] * other[2] - this->data[2] * other[1] + this->data[3] * other[0]),
      (-this->data[0] * other[2] + this->data[1] * other[3] + this->data[2] * other[0] + this->data[3] * other[1]),
      (this->data[0] * other[1] - this->data[1] * other[0] + this->data[2] * other[3] + this->data[3] * other[2]),
      (-this->data[0] * other[0] - this->data[1] * other[1] - this->data[2] * other[2] + this->data[3] * other[3])
    }.normalized();
  }

  /// Multiply this quaternion by a 3-dimensional vector
  vec3<T> operator*(const vec3<T>& other) const
  {
    vec3<T> q = {this->data[0], this->data[1], this->data[2]};
    vec3<T> c = other.cross(q);
    vec3<T> w1 = c * (T)2;
    return other + w1 * this->data[3] + w1.cross(q);
  }

  /// Multiply this quaternion and another
  quat& operator*=(const quat& other)
  {
    *this = other * *this;
    return *this;
  }

  /// Conjugate this quaternion
  void conjugate()
  {
    this->data[0] = -this->data[0];
    this->data[1] = -this->data[1];
    this->data[2] = -this->data[2];
  }

  /// Get a new conjugated quaternion
  [[nodiscard]] quat conjugated() const
  {
    return quat{-this->data[0], -this->data[1], -this->data[2], this->data[3]};
  }

  /// Find the magnitude(length) of this quaternion
  [[nodiscard]] T mag() const
  {
    return std::sqrt(this->data[0] * this->data[0] + this->data[1] * this->data[1] + this->data[2] * this->data[2] + this->data[3] * this->data[3]);
  }

  /// Normalize this quaternion
  void normalize()
  {
    T length = this->mag();
    this->data[0] = this->data[0] / length;
    this->data[1] = this->data[1] / length;
    this->data[2] = this->data[2] / length;
    this->data[3] = this->data[3] / length;
  }

  /// Get a new normalized quaternion
  [[nodiscard]] quat normalized() const
  {
    T length = this->mag();
    return quat{this->data[0] / length, this->data[1] / length, this->data[2] / length, this->data[3] / length};
  }

  /// Get the dot product of this and another quaternion
  [[nodiscard]] T dot(const quat& other) const
  {
    return this->data[3] * other[3] + this->data[0] * other[0] + this->data[1] * other[1] + this->data[2] * other[2];
  }

  /// Get a new inverted quaternion
  [[nodiscard]] quat inverse() const
  {
    T length = this->mag();
    return quat{-this->data[0] / length, -this->data[1] / length, -this->data[2] / length, this->data[3] / length};
  }

  /// Convert this quaternion into euler angles (in radians)
  [[nodiscard]] vec3<T> toEuler() const
  {
    T one = (T)1;
    T two = (T)2;
    T sinr = two * (this->w() * this->x() + this->y() * this->z());
    T cosr = one - (two * (this->x() * this->x() + this->y() * this->y()));
    T roll = std::atan2(sinr, cosr);
    T sinp = two * (this->w() * this->y() - this->z() * this->x());
    T pitch;
    if(std::fabs(sinp) >= 1) pitch = std::copysign(pi<double> / two, sinp);
    else pitch = std::asin(sinp);
    T siny = two * (this->w() * this->z() + this->x() * this->y());
    T cosy = one - (two * (this->y() * this->y() + this->z() * this->z()));
    T yaw = std::atan2(siny, cosy);
    return {roll, pitch, yaw};
  }

  /// Convert euler angles to a quaternion rotation
  /// \param euler {roll, pitch, yaw} in radians
  [[nodiscard]] static quat fromEuler(const vec3<T>& euler)
  {
    quat out;
    double half = 0.5;
    T cYaw, sYaw, cRoll, sRoll, cPitch, sPitch;
    cYaw = std::cos(euler[2] * half);
    sYaw = std::sin(euler[2] * half);
    cRoll = std::cos(euler[0] * half);
    sRoll = std::sin(euler[0] * half);
    cPitch = std::cos(euler[1] * half);
    sPitch = std::sin(euler[1] * half);

    out.w() = cYaw * cRoll * cPitch + sYaw * sRoll * sPitch;
    out.x() = cYaw * sRoll * cPitch - sYaw * cRoll * sPitch;
    out.y() = cYaw * cRoll * sPitch + sYaw * sRoll * cPitch;
    out.z() = sYaw * cRoll * cPitch - cYaw * sRoll * sPitch;
    return out.normalized();
  }

  [[nodiscard]] vec4<T> toAxial() const
  {
    float x, y, z;
    float angle = (T)2 * std::acos(this->w());
    float divisor = std::sqrt(1 - (this->w() * this->w()));
    if(divisor < 0.001f)
    {
      x = this->x();
      y = this->y();
      z = this->z();
    }
    else
    {
      x = this->x() / divisor;
      y = this->y() / divisor;
      z = this->z() / divisor;
    }
    return vec4<T>(x, y, z, angle);
  }

  void fromAxial(const vec4<T>& in)
  {
    float a = in[3] / (T)2;
    float s = std::sin(a);
    this->data[0] = in[0] * s;
    this->data[1] = in[1] * s;
    this->data[2] = in[2] * s;
    this->data[3] = std::cos(a);
    this->normalize();
  }

  /// Convert an axial rotation into a rotation quaternion
  void fromAxial(const T& xIn, const T& yIn, const T& zIn, const T& angle)
  {
    float a = angle / (T)2;
    float s = std::sin(a);
    this->data[0] = xIn * s;
    this->data[1] = yIn * s;
    this->data[2] = zIn * s;
    this->data[3] = std::cos(a);
    this->normalize();
  }

  /// Convert an axial rotation into a rotation quaternion
  void fromAxial(const vec3<T>& xyzIn, const T& angle)
  {
    float a = angle / (T)2;
    float s = std::sin(a);
    this->data[0] = xyzIn[0] * s;
    this->data[1] = xyzIn[1] * s;
    this->data[2] = xyzIn[2] * s;
    this->data[3] = std::cos(a);
    this->normalize();
  }

  /// Calculate a quaternion rotation that aims at the given coordinates
  /// \param originPos Typically the position of the camera
  /// \param targetPos The point in the world to aim at
  /// \param upVec A normalized direction vector specifying what direction up is to be considered
  [[nodiscard]] static quat lookAt(const vec3<T>& originPos, const vec3<T>& targetPos, const vec3<T>& upVec)
  {
    vec3<T> front = targetPos - originPos;
    front.normalize();
    vec3<T> side = front.cross(-upVec);
    side.normalize();
    vec3<T> up = front.cross(side);
    up.normalize();
    mat4x4<T> comp{};
    comp[0][0] = side[0];
    comp[0][1] = side[1];
    comp[0][2] = side[2];
    comp[1][0] = up[0];
    comp[1][1] = up[1];
    comp[1][2] = up[2];
    comp[2][0] = front[0];
    comp[2][1] = front[1];
    comp[2][2] = front[2];
    return quat{comp};
  }

  /// A cumulative version of lookAt
  [[nodiscard]] static quat lookAt(const vec3<T> originPos, const vec3<T> targetPos, const quat& currentRotation, const T lerp = (T)1)
  {
    vec3<T> frontTo = vec3<T>{targetPos - originPos}.normalized() * currentRotation.conjugated();
    return vecDelta({0, 0, 1}, frontTo, lerp);
  }

  /// Create a rotation quaternion to multiply an orientation quaternion by, from relative mouse movement values
  [[nodiscard]] static quat rotateFromMouse(const T xrel, const T yrel, const T lookSensitivity)
  {
    float a = (-xrel * lookSensitivity) / 2.0f;
    quat xQuat = quat{0.0f, std::sin(a), 0.0f, std::cos(a)};
    a = (-yrel * lookSensitivity) / 2.0f;
    quat yQuat = quat{std::sin(a), 0.0f, 0.0f, std::cos(a)};
    return quat{xQuat * yQuat}.normalized();
  }

  [[nodiscard]] static quat vecDelta(const vec3<T> from, const vec3<T> to, const T lerp = (T)1)
  {
    if(lerp < 0) lerp = 0;
    if(lerp > 1) lerp = 1;
    T dot = to.dot(from);
    if(dot > 1) dot = 1;
    if(dot < -1) dot = -1;
    if(dot == 1) return quat{0, 0, 0, 1};
    if(dot == -1) return quat{0, 0, 1, 0};
    T rot = std::acos(dot);
    vec3<T> rotAxis = to.cross(from);
    rotAxis.normalize();
    return axialToQuat(rotAxis.x(), rotAxis.y(), rotAxis.z(), rot * lerp);
  }

  [[nodiscard]] quat limitRotationRange(const vec3<T> up, const T angleLimit, const T lerp = (T)1)
  {
    vec3<T> upQ = -up * this->conjugated();
    upQ.normalize();
    T dot = vec3<T>{0, 1, 0}.dot(upQ);
    if(dot >= 1) return {};
    if(dot < -1) dot = -1;
    T angle = std::acos(dot);
    if(angle > angleLimit) return {};
    vec3<T> rotAxis = vec3<T>{0, 1, 0}.cross(upQ);
    rotAxis.normalize();
    quat out;
    out.fromAxial(rotAxis.x(), rotAxis.y(), rotAxis.z(), (angleLimit - angle) * lerp);
    return out;
  }

  [[nodiscard]] quat correctOrientation(const vec3<T> up, const T lerp = (T)1)
  {
    vec3<T> upQ = up * this->conjugated();
    upQ.normalize();
    vec3<T> side = vec3<T>{0, 0, 1}.cross(-upQ);
    side.normalize();
    if(vec3<T>{0, 1, 0}.dot(upQ) <= 0) side = -side;
    vec3<T> upFixed = vec3<T>{0, 0, 1}.cross(side);
    upFixed.normalize();
    return vecDelta({0, 1, 0}, upFixed, lerp);
  }

  [[nodiscard]] static size_t size()
  {
    return 4;
  }

  /// Get a formatted string of the contents of this quaternion
  [[nodiscard]] std::string toString() const
  {
    std::string out = "(quat)\n[";
    for(int i = 0; i < 4; i++)
    {
      switch(i)
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
        case 3:
          out += "w: ";
          break;
        default: break;
      }
      out += std::to_string(this->data[i]);
      if(i < 3) out += " ";
    }
    out += "]\n";
    return out;
  }

  /// Print this quaternion with printf
  void print(const std::string& name) const
  {
    printf("%s: %s\n", name.data(), this->toString().data());
  }
};
