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

struct Logger
{
	Logger(LogTarget target = LogTarget::STDOUT);
	~Logger();
	
	void setFileTarget(std::string const &filePath);
	
	void log(Severity severity, std::string const &message);
	
	void flush();

private:
	LogTarget target;
	FILE *out = nullptr;
	std::vector<std::string> buf;
};
