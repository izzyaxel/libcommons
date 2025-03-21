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

std::string readTextFile(const std::string& filePath)
{
  std::ifstream fileIn;
  fileIn.open(filePath);
  if(!fileIn)
  {
    printf("Error opening file %s\n", filePath.data());
  }
  
  return {std::istreambuf_iterator<char>(fileIn), std::istreambuf_iterator<char>()};
}

std::vector<uint8_t> readFile(const std::string& filePath)
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

void createDirectory(const std::string& folderPath)
{
#if defined(WINDOWS)
  CreateDirectory(folderPath.data(), nullptr);
#elif defined(LINUX) || defined(OSX)
  mkdir(folderPath.data(), 0755);
#endif
}

void closeFile(FILE*& file)
{
  if(fclose(file) != 0)
  {
    throw std::runtime_error("Failed to close file");
  }
  
  file = nullptr;
}

FILE* openFile(const std::string& name, const std::string& mode)
{
  FILE* out = fopen(name.data(), mode.data());
  if(!out)
  {
    throw std::runtime_error("Failed to open " + name + " with mode " + mode);
  }
  
  return out;
}

size_t readFile(FILE* file, void* destBuffer, const size_t amount, const size_t acceptableTimeouts)
{
  size_t amtRead = 0, timeoutCounter = 0;
  do
  {
    if(timeoutCounter >= acceptableTimeouts)
    {
      throw std::runtime_error("Unable to read from file, timed out after " + std::to_string(acceptableTimeouts) + " 0-length reads");
    }
    
    const size_t read = fread(reinterpret_cast<uint8_t*>(destBuffer) + amtRead, 1, amount - amtRead, file);
    amtRead += read;
    if(read == 0)
    {
      timeoutCounter++;
    }
  }
  while(amtRead < amount);
  
  return amtRead;
}

size_t writeFile(FILE* file, const void* inputBuffer, const size_t amount, const size_t acceptableTimeouts)
{
  size_t amtWritten = 0, timeoutCounter = 0;
  do
  {
    if(timeoutCounter >= acceptableTimeouts)
    {
      throw std::runtime_error("Unable to write to file, timed out after " + std::to_string(acceptableTimeouts) + " 0-length writes");
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
