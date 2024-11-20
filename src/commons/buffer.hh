#pragma once

#include "serialization.hh"

#include <vector>
#include <cstdint>

struct Buffer final : Serializable
{
  using iterator = uint8_t*;
  using const_iterator = uint8_t const*;

  Buffer();
  Buffer(const_iterator begin, const_iterator end);
  Buffer(const Buffer& other);
  Buffer(Buffer&& other) noexcept;
  ~Buffer() override = default;
  Buffer& operator =(const Buffer& other);
  Buffer& operator =(Buffer&& other) noexcept;
  bool operator ==(const Buffer& other);
  [[nodiscard]] iterator begin();
  [[nodiscard]] iterator end();
  [[nodiscard]] const_iterator begin() const;
  [[nodiscard]] const_iterator end() const;

  void serialize(Serializer& serializer) override;
  void deserialize(Serializer& serializer) override;
  void write(const std::vector<uint8_t>& in);
  void write(const uint8_t* in, size_t size);
  void discard(size_t amt);
  [[nodiscard]] size_t size() const;
  [[nodiscard]] uint8_t const* data() const;
  [[nodiscard]] uint8_t* data();
  void push_back(uint8_t val);
  void resize(size_t size);
  void transferTo(Buffer& buffer);

private:
  std::vector<uint8_t> buffer;
};
