#include "commons/logger.hh"

#include <iomanip>

Logger::~Logger()
{
	this->flush();
	fclose(this->out);
}

void Logger::setOptions(LoggerOptions const &options)
{
	if((this->target == LogTarget::FILE || this->target == LogTarget::BOTH) && options.target == LogTarget::STDOUT)
	{
		if(this->out)
		{
			fflush(this->out);
			fclose(this->out);
			this->out = nullptr;
		}
	}
	this->target = options.target;
	this->verbosity = options.verbosity;
	if(!options.logFilePath.empty()) this->setFileTarget(options.logFilePath, options.appendToLogFile);
	this->autoFlush = options.autoFlush;
}

void Logger::setFileTarget(std::string const &filePath, bool append)
{
	if(this->out)
	{
		fflush(this->out);
		fclose(this->out);
	}
	this->out = fopen(filePath.data(), append ? "a" : "w");
	if(!this->out) printf("Failed to start log file\n");
}

void Logger::log(Severity severity, std::string const &message)
{
	if(this->verbosity == LogVerbosity::NONE) return;
	std::stringstream prefix;
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	switch(this->stamping)
	{
		case LogStamping::NONE: break;
		case LogStamping::TIMESTAMPS:
			prefix << std::put_time(&tm, "[%H:%M.%S]");
			break;
		
		case LogStamping ::TIMESTAMPSANDDATES:
			prefix << std::put_time(&tm, "[%d-%m-%Y %H:%M.%S]");
			break;
	}
	switch(severity)
	{
		case Severity::INFO:
			if(this->verbosity == LogVerbosity::HIGH)this->buf.push_back(prefix.str() + " " + message);
			break;
		
		case Severity::ERR:
			if(this->verbosity == LogVerbosity::HIGH || this->verbosity == LogVerbosity::MED) this->buf.push_back(prefix.str() + " [ERROR]: " + message);
			break;
		
		case Severity::FATAL:
			if(this->verbosity == LogVerbosity::HIGH || this->verbosity == LogVerbosity::MED || this->verbosity == LogVerbosity::LOW) this->buf.push_back(prefix.str() + " [FATAL]: " + message);
			break;
	}
	if(this->autoFlush) this->flush();
}

void Logger::flush()
{
	switch(this->target)
	{
		case LogTarget::STDOUT:
			for(auto const &message : this->buf)
			{
				fprintf(stdout, "%s\n", message.data());
			}
			fflush(stdout);
			break;
		
		case LogTarget::FILE:
			for(auto const &message : this->buf)
			{
				fprintf(this->out, "%s\n", message.data());
			}
			fflush(this->out);
			break;
		
		case LogTarget::BOTH:
			for(auto const &message : this->buf)
			{
				fprintf(stdout, "%s\n", message.data());
				fprintf(this->out, "%s\n", message.data());
			}
			fflush(stdout);
			fflush(this->out);
			break;
	}
	
	this->buf.clear();
}
