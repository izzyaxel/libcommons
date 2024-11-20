#pragma once

#include <string>
#include <cstdio>
#include <vector>
#include <sstream>
#include <cstdint>

#define FILEFUNCLINE(funcName) "file: " << __FILE_NAME__ << " func: " << funcName << " line: " << __LINE__
#define FILELINE "file: " << __FILE_NAME__ << " line: " << __LINE__

enum struct Severity
{
  INFO,
  WARNING,
  ERR,
  FATAL,
};

using Sev = Severity;

enum struct LogTarget
{
  FILE,
  STDOUT,
  BOTH,
};

enum struct LogStamping
{
  NONE,
  TIMESTAMPS,
  TIMESTAMPSANDDATES,
};

enum struct LogVerbosity
{
  NONE,
  LOW,
  MED,
  HIGH //low: fatal, med: fatal warning and err, high: fatal warning err and info
};

struct LoggerOptions
{
  LogTarget target = LogTarget::STDOUT;
  LogStamping stamping = LogStamping::NONE;
  LogVerbosity verbosity = LogVerbosity::HIGH;
  std::string logFilePath;
  bool appendToLogFile = false, autoFlush = true;
};

struct Logger
{
  ~Logger();

  std::string endl();
  [[nodiscard]] std::string timestamp() const;

  //Writes into the temporary buffer to construct a log message, must then be pushed to the main buffer
  Logger& operator <<(Sev val);
  Logger& operator <<(const char* val);
  Logger& operator <<(const std::string& val);
  Logger& operator <<(char val);
  Logger& operator <<(double val);
  Logger& operator <<(float val);
  
  template <typename T> Logger& operator <<(const T val)
  {
    this->tempBuf << std::to_string(val);
    return *this;
  }
  template <typename T> Logger& operator <<(T* val)
  {
    this->tempBuf << val;
    return *this;
  }

  /// Push the temporary buffer to the main buffer
  void push();
  void setOptions(const LoggerOptions& options);
  void setFileTarget(const std::string& filePath, bool append = false);
  void setDecimalPlaces(uint8_t numDecimalPlaces);
  void log(Severity severity, const std::string& message);
  void flush();

  private:
  LogTarget target = LogTarget::FILE;
  LogStamping stamping = LogStamping::TIMESTAMPS;
  LogVerbosity verbosity = LogVerbosity::HIGH;
  FILE* out = nullptr;
  std::vector<std::string> buf;
  std::stringstream tempBuf;
  bool autoFlush = true;
  uint8_t decimalPlaces = 6;
};
