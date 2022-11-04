#pragma once

#include <string>
#include <cstdio>
#include <vector>
#include <sstream>
#include "math/fixed.hh"
#include "export.hh"

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
	std::string logFilePath = "";
	bool appendToLogFile = false, autoFlush = true;
};

struct Logger
{
	COMMONSAPI ~Logger();
	
	COMMONSAPI std::string endl();
	[[nodiscard]] COMMONSAPI std::string timestamp();
	
	//Writes into the temporary buffer to construct a log message, must then be pushed to the main buffer
	COMMONSAPI Logger& operator << (Sev val);
	COMMONSAPI Logger& operator << (char const *val);
	COMMONSAPI Logger& operator << (std::string const &val);
	COMMONSAPI Logger& operator << (char val);
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
	
	template<uint32_t bits, typename V> Logger& operator <<(fixed<bits, V> val)
	{
		this->tempBuf << val.toDouble();
		return *this;
	}
	
	/// Push the temporary buffer to the main buffer
	COMMONSAPI void push();
	
	COMMONSAPI void setOptions(LoggerOptions const &options);
	
	COMMONSAPI void setFileTarget(std::string const &filePath, bool append = false);
	
	COMMONSAPI void log(Severity severity, std::string const &message);
	
	COMMONSAPI void flush();

private:
	LogTarget target;
	LogStamping stamping;
	LogVerbosity verbosity;
	FILE *out = nullptr;
	std::vector<std::string> buf;
	std::stringstream tempBuf;
	bool autoFlush = true;
};
