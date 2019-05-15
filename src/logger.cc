#include "commons/logger.hh"

Logger::Logger(std::string const &filePath)
{
	this->out = fopen(filePath.data(), "w");
	if(!this->out) printf("Failed to start log file\n");
}

Logger::~Logger()
{
	this->flush();
	fclose(this->out);
}

void Logger::log(Severity severity, std::string const &message)
{
	switch(severity)
	{
		case Severity::INFO:
			this->buf.push_back(message);
			break;
		
		case Severity::ERROR:
			this->buf.push_back("[ERROR]: " + message);
			break;
		
		case Severity::FATAL:
			this->buf.push_back("[FATAL]: " + message);
			break;
	}
}

void Logger::flush()
{
	for(auto const &message : this->buf)
	{
		fprintf(this->out, "%s\n", message.data());
	}
	fflush(this->out);
	this->buf.clear();
}
