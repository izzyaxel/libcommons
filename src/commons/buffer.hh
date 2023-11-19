#pragma once

#include "serialization.hh"
#include "export.hh"

#include <vector>
#include <cstdint>

struct Buffer : public Serializable //TODO finish buffer
{
  COMMONS_API void serialize(Serializer &serializer) override;

  COMMONS_API void deserialize(Serializer &serializer) override;

  using iterator = uint8_t*;
  using const_iterator = uint8_t const*;

  COMMONS_API Buffer();

  COMMONS_API Buffer(const_iterator begin, const_iterator end);

  COMMONS_API Buffer(Buffer const &other);

  COMMONS_API Buffer(Buffer &&other);

  COMMONS_API ~Buffer();

  COMMONS_API Buffer& operator =(Buffer const &other);

  COMMONS_API Buffer& operator =(Buffer &&other);

  COMMONS_API bool operator ==(Buffer const &other);

  [[nodiscard]] COMMONS_API inline iterator begin() { return nullptr; } //TODO
  [[nodiscard]] COMMONS_API inline iterator end() { return nullptr; }
  [[nodiscard]] COMMONS_API inline const_iterator begin() const { return nullptr; }
  [[nodiscard]] COMMONS_API inline const_iterator end() const { return nullptr; }

  COMMONS_API void write(std::vector<uint8_t> const &in);

  COMMONS_API void write(uint8_t const* in, size_t size);

  COMMONS_API void discard(size_t amt);

  [[nodiscard]] COMMONS_API size_t size();

  [[nodiscard]] COMMONS_API uint8_t const* data() const;

  [[nodiscard]] COMMONS_API uint8_t* data();

  COMMONS_API void push_back(uint8_t val);

  COMMONS_API void resize(size_t size);

  COMMONS_API void transferTo(Buffer &buffer);

private:
  std::vector<uint8_t> buffer;
};
