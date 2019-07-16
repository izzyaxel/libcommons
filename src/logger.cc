#include "commons/logger.hh"

Logger::Logger(LogTarget target) : target(target) {}

Logger::~Logger()
{
	this->flush();
	fclose(this->out);
}

void Logger::setFileTarget(std::string const &filePath)
{
	if(this->out)
	{
		fflush(this->out);
		fclose(this->out);
	}
	this->out = fopen(filePath.data(), "w");
	if(!this->out) printf("Failed to start log file\n");
}

void Logger::log(Severity severity, std::string const &message)
{
	switch(severity)
	{
		case Severity::INFO:
			this->buf.push_back(message);
			break;
		
		case Severity::ERR:
			this->buf.push_back("[ERROR]: " + message);
			break;
		
		case Severity::FATAL:
			this->buf.push_back("[FATAL]: " + message);
			break;
	}
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
