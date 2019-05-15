#pragma once

#include <string>
#include <cstdio>
#include <vector>

enum struct Severity
{
	INFO, ERROR, FATAL,
};

struct Logger
{
	Logger() = default;
	explicit Logger(std::string const &filePath);
	~Logger();
	
	void log(Severity severity, std::string const &message);
	
	void flush();

private:
	FILE *out = nullptr;
	std::vector<std::string> buf;
};
