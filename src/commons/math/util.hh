#pragma once

#include "vec3.hh"
#include "mat4.hh"
#include "general.hh"

/// Check if the given vertex is within the camera's frustum
/// \param mvp The completed model view projection matrix of the camera you want to check visibility with
/// \param vertex
template <typename T>
[[nodiscard]] bool isVertexOnscreen(const mat4x4<T>& mvp, const vec3<T>& vertex)
{
  vec3<T> result = vec3<T>{vec4<T>{vertex, (T)1} * mvp};
  return result.x() < (T)1 && result.x() > (T)-1 && result.y() < (T)1 && result.y() > (T)-1 && result.z() < (T)1 && result.z() > (T)-1;
}

/// Translate a mouse coordinate over the openGL window to a ray into 3D space
template <typename T>
[[nodiscard]] vec3<T> mouseToWorld(const int32_t clickX, const int32_t clickY, const mat4x4<T>& view, const mat4x4<T>& projection, const uint32_t width, const uint32_t height)
{
  mat4x4<T> inv = mat4x4<T>(view * projection).inverse();
  double ndcX = ((double)clickX / (double)width) * (double)2 - (double)1;
  double ndcY = ((double)clickY / (double)height) * (double)2 - (double)1;
  vec4<T> clip = {(T)ndcX, (T)ndcY, (T)1, (T)1};
  clip = inv * clip;
  clip /= clip[3];
  return vec3<T>{clip};
}

/// Is the given value is within a range of the target value
template <typename T>
bool within(const T val, const T target, const T range)
{
  return (val + range) <= (target + range) && (val - range) >= (target - range);
}
