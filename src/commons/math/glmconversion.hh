#pragma once

#if __has_include("glm/glm.hpp")
#include "vec2.hh"
#include "vec3.hh"
#include "vec4.hh"
#include "mat3.hh"
#include "mat4.hh"

//To GLM
template <typename T>
[[nodiscard]] glm::vec2 toGLMvec2(const vec2<T>& in)
{
  glm::vec2 out = glm::vec2{in[0], in[1]};
  return out;
}

template <typename T>
[[nodiscard]] glm::vec3 toGLMvec3(const vec3<T>& in)
{
  glm::vec3 out = glm::vec3{in[0], in[1], in[2]};
  return out;
}

template <typename T>
[[nodiscard]] glm::vec4 toGLMvec4(const vec4<T>& in)
{
  glm::vec4 out = glm::vec4{in[0], in[1], in[2], in[3]};
  return out;
}

template <typename T>
[[nodiscard]] glm::mat3x3 toGLMmat3(const mat3x3<T>& in)
{
  glm::mat3x3 out;
  out[0][0] = in[0][0];
  out[0][1] = in[0][1];
  out[0][2] = in[0][2];
  out[1][0] = in[1][0];
  out[1][1] = in[1][1];
  out[1][2] = in[1][2];
  out[2][0] = in[2][0];
  out[2][1] = in[2][1];
  out[2][2] = in[2][2];
  return out;
}

template <typename T>
[[nodiscard]] glm::mat4x4 toGLMmat4(const mat4x4<T>& in)
{
  glm::mat4x4 out;
  out[0][0] = in[0][0];
  out[0][1] = in[0][1];
  out[0][2] = in[0][2];
  out[0][3] = in[0][3];
  out[1][0] = in[1][0];
  out[1][1] = in[1][1];
  out[1][2] = in[1][2];
  out[1][3] = in[1][3];
  out[2][0] = in[2][0];
  out[2][1] = in[2][1];
  out[2][2] = in[2][2];
  out[2][3] = in[2][3];
  out[3][0] = in[3][0];
  out[3][1] = in[3][1];
  out[3][2] = in[3][2];
  out[3][3] = in[3][3];
  return out;
}

//From GLM
template <typename T>
[[nodiscard]] vec2<T> fromGLMvec2(const glm::vec2& in)
{
  vec2<T> out = {in[0], in[1]};
  return out;
}

template <typename T>
[[nodiscard]] vec3<T> fromGLMvec3(const glm::vec3& in)
{
  vec3<T> out = {in[0], in[1], in[2]};
  return out;
}

template <typename T>
[[nodiscard]] vec4<T> fromGLMvec4(const glm::vec4& in)
{
  vec4<T> out = {in[0], in[1], in[2], in[3]};
  return out;
}

template <typename T>
[[nodiscard]] mat3x3<T> fromGLMmat3(const glm::mat3x3& in)
{
  mat3x3<T> out;
  out[0][0] = in[0][0];
  out[0][1] = in[0][1];
  out[0][2] = in[0][2];
  out[1][0] = in[1][0];
  out[1][1] = in[1][1];
  out[1][2] = in[1][2];
  out[2][0] = in[2][0];
  out[2][1] = in[2][1];
  out[2][2] = in[2][2];
  return out;
}

template <typename T>
[[nodiscard]] mat4x4<T> fromGLMmat4(const glm::mat4x4& in)
{
  mat4x4<T> out;
  out[0][0] = in[0][0];
  out[0][1] = in[0][1];
  out[0][2] = in[0][2];
  out[0][3] = in[0][3];
  out[1][0] = in[1][0];
  out[1][1] = in[1][1];
  out[1][2] = in[1][2];
  out[1][3] = in[1][3];
  out[2][0] = in[2][0];
  out[2][1] = in[2][1];
  out[2][2] = in[2][2];
  out[2][3] = in[2][3];
  out[3][0] = in[3][0];
  out[3][1] = in[3][1];
  out[3][2] = in[3][2];
  out[3][3] = in[3][3];
  return out;
}
#endif
