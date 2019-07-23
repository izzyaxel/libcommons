#pragma once

#include <string>
#include <cstdio>
#include <vector>

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
	bool autoFlush = true;
};
