#pragma once

#include <vector>
#include <cstdint>
#include <cstring>
#include "export.hh"

enum struct SeekPos
{
  BEG = 0,
  CUR,
  END
};

/// A read-only in-memory buffer, mimics C's file I/O API
template <typename T> struct DataBuffer
{
  DataBuffer() = default;

  COMMONS_API explicit DataBuffer(const std::vector<T>& buffer)
  {
    const size_t convSize = sizeof(T) * buffer.size();
    const uint8_t* tmp = reinterpret_cast<const uint8_t*>(buffer.data());
    this->buffer = {tmp, tmp + convSize};
  }
  COMMONS_API DataBuffer(const T* src, const size_t size)
  {
    const size_t convSize = sizeof(T) * size;
    const uint8_t* tmp = reinterpret_cast<const uint8_t*>(src);
    this->buffer = {tmp, tmp + convSize};
  }

  COMMONS_API size_t read(void* dst, size_t amt);
  COMMONS_API void rewind();
  COMMONS_API bool seek(size_t amt, SeekPos seekPos);
  [[nodiscard]] COMMONS_API size_t tell() const;

  private:
  size_t pos = 0;
  std::vector<uint8_t> buffer{};
  
  void sanity();
};
