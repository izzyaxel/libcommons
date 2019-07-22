#pragma once

#include <string>
#include <cstdio>
#include <vector>

enum struct Severity
{
	INFO, ERR, FATAL,
};

enum struct LogTarget
{
	FILE, STDOUT, BOTH
};

enum struct LogVerbosity
{
	NORMAL, TIMESTAMPS, TIMESTAMPSANDDATES
};

struct LoggerOptions
{
	LogTarget target = LogTarget::STDOUT;
	LogVerbosity verbosity = LogVerbosity::NORMAL;
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
	LogVerbosity verbosity;
	FILE *out = nullptr;
	std::vector<std::string> buf;
	bool autoFlush = true;
};
