#pragma once

#include <string>
#include <cstdio>
#include <vector>
#include <sstream>
#include <cstdint>
#include "export.hh"

#define FILEFUNCLINE(funcName) "file: " << __FILE_NAME__ << " func: " << funcName << " line: " << __LINE__
#define FILELINE "file: " << __FILE_NAME__ << " line: " << __LINE__

enum struct Severity
{
	INFO, ERR, FATAL,
};
using Sev = Severity;

enum struct LogTarget
{
	FILE, STDOUT, BOTH,
};

enum struct LogStamping
{
	NONE, TIMESTAMPS, TIMESTAMPSANDDATES,
};

enum struct LogVerbosity
{
	NONE, LOW, MED, HIGH //low: fatal, med: fatal and err, high: fatal, err, and info
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
	COMMONS_API ~Logger();
	
	COMMONS_API std::string endl();
	[[nodiscard]] COMMONS_API std::string timestamp();
	
	//Writes into the temporary buffer to construct a log message, must then be pushed to the main buffer
	COMMONS_API Logger& operator << (Sev val);
	COMMONS_API Logger& operator << (char const *val);
	COMMONS_API Logger& operator << (std::string const &val);
	COMMONS_API Logger& operator << (char val);
	COMMONS_API Logger& operator << (double val);
	COMMONS_API Logger& operator << (float val);
	template <typename T> Logger& operator << (T val)
	{
		this->tempBuf << std::to_string(val);
		return *this;
	}
	template <typename T> Logger& operator << (T *val)
	{
		this->tempBuf << val;
		return *this;
	}
	
	/// Push the temporary buffer to the main buffer
	COMMONS_API void push();
	
	COMMONS_API void setOptions(LoggerOptions const &options);
	
	COMMONS_API void setFileTarget(std::string const &filePath, bool append = false);
	
	COMMONS_API void setDecimalPlaces(uint8_t numDecimalPlaces);
	
	COMMONS_API void log(Severity severity, std::string const &message);
	
	COMMONS_API void flush();

private:
	LogTarget target = LogTarget::FILE;
	LogStamping stamping = LogStamping::TIMESTAMPS;
	LogVerbosity verbosity = LogVerbosity::HIGH;
	FILE *out = nullptr;
	std::vector<std::string> buf;
	std::stringstream tempBuf;
	bool autoFlush = true;
	uint8_t decimalPlaces= 6;
};
