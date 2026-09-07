#include "commons/fileio.hh"

#include <stdexcept>
#include <fstream>

#if defined(WINDOWS)
#include <windows.h>
#include <libloaderapi.h>
#elif defined(LINUX) || defined(OSX)
#include <sys/stat.h>
#include <unistd.h>
#endif

auto readTextFile(const std::string& filePath) -> std::string
{
  std::ifstream fileIn;
  fileIn.open(filePath);
  if(!fileIn)
  {
    printf("Error opening file %s\n", filePath.data());
  }
  
  return {std::istreambuf_iterator(fileIn), std::istreambuf_iterator<char>()};
}

auto readFile(const std::string& filePath) -> std::vector<uint8_t>
{
  FILE* in = fopen(filePath.data(), "rb");
  if(!in)
  {
    printf("File reader: failed to read input file: %s\n", filePath.data());
    return {};
  }
  fseek(in, 0, SEEK_END);
  const size_t len = (size_t)ftell(in);
  rewind(in);
  std::vector<uint8_t> data;
  data.resize(len);
  size_t r = fread(data.data(), 1, len, in);
  fclose(in);
  return data;
}

auto createDirectory(const std::string& folderPath) -> void
{
#if defined(WINDOWS)
  CreateDirectory(folderPath.data(), nullptr);
#elif defined(LINUX) || defined(OSX)
  mkdir(folderPath.data(), 0755);
#endif
}

auto closeFile(FILE*& file) -> void
{
  if(fclose(file) != 0)
  {
    printf("Failed to close file\n");
    return;
  }
  
  file = nullptr;
}

auto openFile(const std::string& name, const std::string& mode) -> FILE*
{
  FILE* out = fopen(name.data(), mode.data());
  if(!out)
  {
    printf("Failed to open %s with mode %s\n", name.c_str(), mode.c_str());
    return nullptr;
  }
  
  return out;
}

auto readFile(FILE* file, void* destBuffer, const size_t amount, const size_t acceptableTimeouts) -> size_t
{
  size_t amtRead = 0, timeoutCounter = 0;
  do
  {
    if(timeoutCounter >= acceptableTimeouts)
    {
      printf("Unable to read from file, timed out after %zu 0-length reads\n", acceptableTimeouts);
      return 0;
    }
    
    const size_t read = fread(static_cast<uint8_t*>(destBuffer) + amtRead, 1, amount - amtRead, file);
    amtRead += read;
    if(read == 0)
    {
      timeoutCounter++;
    }
  }
  while(amtRead < amount);
  
  return amtRead;
}

auto writeFile(FILE* file, const void* inputBuffer, const size_t amount, const size_t acceptableTimeouts) -> size_t
{
  size_t amtWritten = 0, timeoutCounter = 0;
  do
  {
    if(timeoutCounter >= acceptableTimeouts)
    {
      printf("Unable to write to file, timed out after %zu 0-length writes\n", acceptableTimeouts);
      return 0;
    }
    const size_t wrote = fwrite(inputBuffer, 1, amount - amtWritten, file);
    amtWritten += wrote;
    if(wrote == 0)
    {
      timeoutCounter++;
    }
  }
  while(amtWritten < amount);
  
  return amtWritten;
}
