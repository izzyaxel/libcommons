#pragma once

#include <string>
#include <cstdio>
#include <vector>
#include <sstream>

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
	~Logger();
	
	std::string endl();
	[[nodiscard]] std::string timestamp();
	
	//Writes into the temporary buffer to construct a log message, must then be pushed to the main buffer
	Logger& operator << (Sev val);
	Logger& operator << (char const *val);
	Logger& operator << (std::string const &val);
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
	void push();
	
	void setOptions(LoggerOptions const &options);
	
	void setFileTarget(std::string const &filePath, bool append = false);
	
	void log(Severity severity, std::string const &message);
	
	void flush();

private:
	LogTarget target;
	LogStamping stamping;
	LogVerbosity verbosity;
	FILE *out = nullptr;
	std::vector<std::string> buf;
	std::stringstream tempBuf;
	bool autoFlush = true;
};
