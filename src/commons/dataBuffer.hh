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
struct DataBuffer
{
  DataBuffer() = default;
  COMMONS_API explicit DataBuffer(std::vector<uint8_t> buffer);
  COMMONS_API DataBuffer(const uint8_t* src, size_t size);
  
  COMMONS_API size_t read(void* dst, size_t amt);
  COMMONS_API void rewind();
  COMMONS_API bool seek(size_t amt, SeekPos seekPos);
  [[nodiscard]] COMMONS_API size_t tell() const;
  [[nodiscard]] COMMONS_API const uint8_t* data() const;

  private:
  size_t pos = 0;
  std::vector<uint8_t> buffer{};
  
  void sanity();
};
