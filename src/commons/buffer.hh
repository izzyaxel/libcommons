#pragma once

#include "serialization.hh"
#include "export.hh"

#include <vector>
#include <cstdint>

struct Buffer final : Serializable
{
  using iterator = uint8_t*;
  using const_iterator = uint8_t const*;

  COMMONS_API Buffer();
  COMMONS_API Buffer(const_iterator begin, const_iterator end);
  COMMONS_API Buffer(const Buffer& other);
  COMMONS_API Buffer(Buffer&& other) noexcept;
  COMMONS_API ~Buffer() override = default;
  COMMONS_API Buffer& operator =(const Buffer& other);
  COMMONS_API Buffer& operator =(Buffer&& other) noexcept;
  COMMONS_API bool operator ==(const Buffer& other);
  [[nodiscard]] COMMONS_API iterator begin();
  [[nodiscard]] COMMONS_API iterator end();
  [[nodiscard]] COMMONS_API const_iterator begin() const;
  [[nodiscard]] COMMONS_API const_iterator end() const;

  COMMONS_API void serialize(Serializer& serializer) override;
  COMMONS_API void deserialize(Serializer& serializer) override;
  COMMONS_API void write(const std::vector<uint8_t>& in);
  COMMONS_API void write(const uint8_t* in, size_t size);
  COMMONS_API void discard(size_t amt);
  [[nodiscard]] COMMONS_API size_t size() const;
  [[nodiscard]] COMMONS_API uint8_t const* data() const;
  [[nodiscard]] COMMONS_API uint8_t* data();
  COMMONS_API void push_back(uint8_t val);
  COMMONS_API void resize(size_t size);
  COMMONS_API void transferTo(Buffer& buffer);

private:
  std::vector<uint8_t> buffer;
};
