#pragma once

#include "vec2.hh"
#include "vec3.hh"
#include "general.hh"

//Value
/// Adjustable lerp
/// \param a Start
/// \param b End
/// \param progress 0-1
/// \param curve ==1 is linear, >1 is ease in-out, <1 is inverse ease in-out
template <typename T>
[[nodiscard]] T alerp(const T a, const T b, const T progress, const T curve)
{
  T expProg = std::pow(progress, curve);
  T lerp = expProg / (expProg + std::pow((T)1 - progress, curve));
  return ((T)1 - lerp) * a + lerp * b;
}

/// Logarithmic lerp, return value approaches b logarithmically faster as progress approaches 1
/// \param a Start
/// \param b End
/// \param progress 0-1
template <typename T>
[[nodiscard]] T loglerp(const T a, const T b, const T progress)
{
  return a * std::pow(b / a, progress);
}

/// Framerate independent linear interpolation
/// \param current Start point, this will be updated with the interpolated value
/// \param to End point
/// \param decay Exponential decay value, hold constant for each 'current' (useful range: 1 - 25)
/// \param deltaTime Time since the last frame occurred
template <typename T, typename U, typename V>
void integraldeltalerp(T& current, const T to, const U decay, const V deltaTime)
{
  current = to + (current - to) * std::exp(-decay * deltaTime);
}

/// Standard linear interpolation
/// \param a Start
/// \param b End
/// \param progress 0-1
template <typename T>
[[nodiscard]] T lerp(const T a, const T b, const T progress)
{
  return a * std::pow(b / a, progress);
}

//Vec2
/// Lerp between 2 2-dimensional vectors
template <typename T>
[[nodiscard]] vec2<T> lerpV2(const vec2<T>& src, const vec2<T>& dest, const float progress)
{
  vec2<T> out;
  out[0] = progress * dest[0] + (1 - progress) * src[0];
  out[1] = progress * dest[1] + (1 - progress) * src[1];
  return out;
}

/// Ease out lerp: fast in slow out
template <typename T>
[[nodiscard]] vec2<T> eoerpV2(const vec2<T>& src, const vec2<T>& dest, const float progress)
{
  return lerpV2(src, dest, (float)(std::sin(progress * pi<T> * (T)0.5)));
}

/// Ease in lerp: slow in fast out
template <typename T>
[[nodiscard]] vec2<T> eierpV2(const vec2<T>& src, const vec2<T>& dest, const float progress)
{
  return lerpV2(src, dest, (float)((T)1.0 - std::cos(progress * pi<T> * (T)0.5)));
}

/// Exponential ease out lerp: fast in slower out
template <typename T>
[[nodiscard]] vec2<T> exeoerpV2(const vec2<T>& src, const vec2<T>& dest, float progress)
{
  return lerpV2(src, dest, (float)(std::sin((progress * progress) * pi<T> * (T)0.5)));
}

/// Exponential ease in lerp: slower in fast out
template <typename T> [[nodiscard]] vec2<T> exeierpV2(const vec2<T>& src, const vec2<T>& dest, const float progress)
{
  return lerpV2(src, dest, (float)((T)1.0 - std::cos((progress * progress) * pi<T> * (T)0.5)));
}

/// Smoothstep lerp: slow in slow out
template <typename T> [[nodiscard]] vec2<T> serpV2(const vec2<T>& src, const vec2<T>& dest, const float progress)
{
  return lerpV2(src, dest, (float)((progress * progress) * ((T)3.0 - ((T)2.0 * progress))));
}

/// Smootherstep lerp: slower in slower out
template <typename T> [[nodiscard]] vec2<T> sserpV2(const vec2<T>& src, const vec2<T>& dest, const float progress)
{
  return lerpV2(src, dest, (float)(std::pow(progress, 3) * (progress * ((T)6.0 * progress - (T)15.0) + (T)10.0)));
}


//Vec3
/// Lerp between 2 3-dimensional vectors
template <typename T>
[[nodiscard]] vec3<T> lerpV3(const vec3<T>& src, const vec3<T>& dest, const float progress)
{
  vec3<T> out;
  out[0] = progress * dest[0] + ((T)1.0 - progress) * src[0];
  out[1] = progress * dest[1] + ((T)1.0 - progress) * src[1];
  out[2] = progress * dest[2] + ((T)1.0 - progress) * src[2];
  return out;
}

/// Ease out lerp: fast in slow out
template <typename T>
[[nodiscard]] vec3<T> eoerpV3(const vec3<T>& src, const vec3<T>& dest, const float progress)
{
  return lerpV3(src, dest, (float)(std::sin(progress * pi<T> * (T)0.5)));
}

/// Ease in lerp: slow in fast out
template <typename T>
[[nodiscard]] vec3<T> eierpV3(const vec3<T>& src, const vec3<T>& dest, const float progress)
{
  return lerpV3(src, dest, (float)((T)1.0 - std::cos(progress * pi<T> * (T)0.5)));
}

/// Exponential ease out lerp: fast in slower out
template <typename T>
[[nodiscard]] vec3<T> exeoerpV3(const vec3<T>& src, const vec3<T>& dest, const float progress)
{
  return lerpV3(src, dest, (float)(std::sin((progress * progress) * pi<T> * (T)0.5)));
}

/// Exponential ease in lerp slower in fast out
template <typename T>
[[nodiscard]] vec3<T> exeierpV3(const vec3<T>& src, const vec3<T>& dest, const float progress)
{
  return lerpV3(src, dest, (float)((T)1.0 - std::cos((progress * progress) * pi<T> * (T)0.5)));
}

/// Smoothstep lerp: slow in slow out
template <typename T>
[[nodiscard]] vec3<T> serpV3(const vec3<T>& src, const vec3<T>& dest, const float progress)
{
  return lerpV3(src, dest, (float)((progress * progress) * ((T)3.0 - ((T)2.0 * progress))));
}

/// Smootherstep lerp: slower in slower out
template <typename T>
[[nodiscard]] vec3<T> sserpV3(const vec3<T>& src, const vec3<T>& dest, const float progress)
{
  return lerpV3(src, dest, (float)(std::pow(progress, 3) * (progress * ((T)6.0 * progress - (T)15.0) + (T)10.0)));
}


//Vec4
/// Lerp between 2 4-dimensional vectors
template <typename T>
[[nodiscard]] vec4<T> lerpV4(const vec4<T>& src, const vec4<T>& dest, float progress)
{
  vec4<T> out;
  out[0] = progress * dest[0] + (1 - progress) * src[0];
  out[1] = progress * dest[1] + (1 - progress) * src[1];
  out[2] = progress * dest[2] + (1 - progress) * src[2];
  out[3] = progress * dest[3] + (1 - progress) * src[3];
  return out;
}

/// Ease out lerp: fast in slow out
template <typename T>
[[nodiscard]] vec4<T> eoerpV4(const vec4<T>& src, const vec4<T>& dest, const float progress)
{
  return lerpV4(src, dest, (float)(std::sin(progress * pi<T> * (T)0.5)));
}

/// Ease in lerp: slow in fast out
template <typename T>
[[nodiscard]] vec4<T> eierpV4(const vec4<T>& src, const vec4<T>& dest, const float progress)
{
  return lerpV4(src, dest, (float)((T)1.0 - std::cos(progress * pi<T> * (T)0.5)));
}

/// Exponential ease out lerp: fast in slower out
template <typename T>
[[nodiscard]] vec4<T> exeoerpV4(const vec4<T>& src, const vec4<T>& dest, const float progress)
{
  return lerpV4(src, dest, (float)(std::sin((progress * progress) * pi<T> * (T)0.5)));
}

/// Exponential ease in lerp: slower in fast out
template <typename T>
[[nodiscard]] vec4<T> exeierpV4(const vec4<T>& src, const vec4<T>& dest, const float progress)
{
  return lerpV4(src, dest, (float)((T)1.0 - std::cos((progress * progress) * pi<T> * (T)0.5)));
}

/// Smoothstep lerp: slow in slow out
template <typename T>
[[nodiscard]] vec4<T> serpV4(const vec4<T>& src, const vec4<T>& dest, const float progress)
{
  return lerpV4(src, dest, (float)((progress * progress) * ((T)3.0 - ((T)2.0 * progress))));
}

/// Smootherstep lerp: slower in slower out
template <typename T>
[[nodiscard]] vec4<T> sserpV4(const vec4<T>& src, const vec4<T>& dest, const float progress)
{
  return lerpV4(src, dest, (float)(std::pow(progress, 3) * (progress * ((T)6.0 * progress - (T)15.0) + (T)10.0)));
}

//Quat
/// Quaternion spherical linear interpolation
template <typename T>
[[nodiscard]] quat<T> slerpQuat(const quat<T>& A, const quat<T>& B, const T value)
{
  T dot = A[0] * B[0] + A[1] * B[1] + A[2] * B[2] + A[3] * B[3];
  if(dot > 1) dot = 1;
  if(dot < -1) dot = -1;
  if(dot == 1) return A;
  T angle = std::acos(dot);
  T sqi = std::sqrt((T)1 - dot * dot);
  T vA = std::sin(((T)1 - value) * angle) / sqi;
  T vB = std::sin(value * angle) / sqi;
  return quat<T>{
    A[0] * vA + B[0] * vB,
    A[1] * vA + B[1] * vB,
    A[2] * vA + B[2] * vB,
    A[3] * vA + B[3] * vB
  }.normalized();
}
