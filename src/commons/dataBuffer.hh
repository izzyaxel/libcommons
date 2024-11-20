#pragma once

#include <vector>
#include <cstdint>
#include <cstring>

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
  explicit DataBuffer(std::vector<uint8_t> buffer);
  DataBuffer(const uint8_t* src, size_t size);
  
  size_t read(void* dst, size_t amt);
  void rewind();
  bool seek(size_t amt, SeekPos seekPos);
  [[nodiscard]] size_t tell() const;
  [[nodiscard]] bool eof() const;
  [[nodiscard]] uint8_t* data();

  private:
  size_t pos = 0;
  std::vector<uint8_t> buffer{};
  
  void sanity();
};
