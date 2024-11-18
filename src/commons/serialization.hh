#pragma once

#include <cstdint>
#include <cstring>
#include <vector>
#include <string>
#include "export.hh"

struct Serializer
{
  COMMONS_API void writeString(const std::string& in)
  {
    this->write<size_t>(in.size());
    this->data.insert(this->data.end(), reinterpret_cast<uint8_t const*>(in.data()), reinterpret_cast<uint8_t const*>(in.data()) + in.size());
  }

  template <typename T> void writeContainer(const T& in)
  {
    this->write<size_t>(in.size());
    this->data.insert(this->data.end(), reinterpret_cast<uint8_t const*>(in.data()), reinterpret_cast<uint8_t const*>(in.data()) + in.size());
  }

  template <typename T, typename = std::enable_if_t<std::is_standard_layout_v<T> && std::is_trivial_v<T> && !std::is_pointer_v<T>>> void write(const T in)
  {
    this->data.insert(this->data.end(), reinterpret_cast<uint8_t const*>(&in), reinterpret_cast<uint8_t const*>(&in) + sizeof(T));
  }

  COMMONS_API void read(uint8_t* dest, const size_t size)
  {
    memcpy(dest, this->data.data() + this->readOffset, size);
    this->readOffset += size;
    this->sz -= size;
  }

  COMMONS_API void readString(std::string& out)
  {
    size_t stringSize = 0;
    this->read<size_t>(stringSize);
    out.resize(stringSize);
    this->read(reinterpret_cast<uint8_t*>(out.data()), stringSize);
  }

  template <typename T> void readContainer(T& out)
  {
    size_t containerSize = 0;
    this->read<size_t>(containerSize);
    this->read(reinterpret_cast<uint8_t*>(&out), containerSize);
  }

  template <typename T, typename = std::enable_if_t<std::is_standard_layout_v<T> && std::is_trivial_v<T> && !std::is_pointer_v<T>>> void read(T& out)
  {
    this->read(reinterpret_cast<uint8_t*>(&out), sizeof(T));
  }

  [[nodiscard]] COMMONS_API size_t size() const
  {
    return this->sz;
  }

  COMMONS_API void end()
  {
    this->readOffset = 0;
    this->data.clear();
  }

private:
  size_t sz = 0;
  size_t readOffset = 0;
  std::vector<uint8_t> data;
};

struct Serializable
{
  COMMONS_API virtual ~Serializable() = default;

  COMMONS_API virtual void serialize(Serializer& serializer) = 0;

  COMMONS_API virtual void deserialize(Serializer& serializer) = 0;

protected:
  Serializable() = default;
};
