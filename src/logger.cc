#include "commons/logger.hh"
#include "commons/stringtools.hh"

#include <iomanip>

std::string Logger::endl()
{
  if(this->autoFlush)
  {
    this->push();
    this->flush();
  }
  else
  {
    this->tempBuf << "\n";
  }
  return "";
}

std::string Logger::timestamp() const
{
  std::stringstream prefix;
  const auto t = std::time(nullptr);
  const auto tm = *std::localtime(&t);
  
  switch(this->stamping)
  {
    case LogStamping::NONE:
    {
      break;
    }
    
    case LogStamping::TIMESTAMPS:
    {
      prefix << std::put_time(&tm, "[%H:%M.%S]");
      break;
    }

    case LogStamping::TIMESTAMPSANDDATES:
    {
      prefix << std::put_time(&tm, "[%d-%m-%Y %H:%M.%S]");
      break;
    }
  }
  
  return prefix.str();
}

Logger::~Logger()
{
  this->flush();
  fclose(this->out);
}

Logger& Logger::operator<<(const Sev val)
{
  switch(val)
  {
    case Sev::INFO:
    {
      break;
    }
    
    case Sev::ERR:
    {
      this->tempBuf << "[ERROR]: ";
      break;
    }
    
    case Sev::WARNING:
    {
      this->tempBuf << "[WARNING]: ";
      break;
    }
    
    case Sev::FATAL:
    {
      this->tempBuf << "[FATAL]: ";
      break;
    }
  }
  return *this;
}

Logger& Logger::operator<<(const char* val)
{
  this->tempBuf << val;
  return *this;
}

Logger& Logger::operator<<(const std::string& val)
{
  this->tempBuf << val;
  return *this;
}

Logger& Logger::operator<<(const char val)
{
  this->tempBuf << val;
  return *this;
}

Logger& Logger::operator<<(const double val)
{
  std::stringstream tmpSS;
  tmpSS << val;
  std::string tmpStr = tmpSS.str();
  const size_t periodLoc = tmpStr.find_last_of('.') + 1;
  const size_t numDec = tmpStr.size() - periodLoc;
  
  if(this->decimalPlaces >= numDec)
  {
    this->tempBuf << val;
    return *this;
  }
  
  tmpStr = subString(tmpStr, 0, tmpStr.size() - (periodLoc + this->decimalPlaces));
  this->tempBuf << tmpStr;
  return *this;
}

Logger& Logger::operator<<(const float val)
{
  std::stringstream tmpSS;
  tmpSS << val;
  std::string tmpStr = tmpSS.str();
  size_t periodLoc = tmpStr.find_last_of('.') + 1;
  size_t numDec = tmpStr.size() - periodLoc;
  
  if(this->decimalPlaces >= numDec)
  {
    this->tempBuf << val;
    return *this;
  }
  
  tmpStr = subString(tmpStr, 0, tmpStr.size() - (periodLoc + this->decimalPlaces));
  this->tempBuf << tmpStr;
  return *this;
}

void Logger::push()
{
  this->buf.push_back(this->tempBuf.str());
  this->tempBuf.str(std::string());
}

void Logger::setOptions(const LoggerOptions& options)
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
  this->stamping = options.stamping;
  this->verbosity = options.verbosity;
  
  if(!options.logFilePath.empty())
  {
    this->setFileTarget(options.logFilePath, options.appendToLogFile);
  }
  
  this->autoFlush = options.autoFlush;
}

void Logger::setFileTarget(const std::string& filePath, const bool append)
{
  if(this->out)
  {
    fflush(this->out);
    fclose(this->out);
  }
  
  this->out = fopen(filePath.data(), append ? "a" : "w");
  
  if(!this->out)
  {
    printf("Failed to start log file\n");
  }
}

void Logger::setDecimalPlaces(const uint8_t numDecimalPlaces)
{
  this->decimalPlaces = numDecimalPlaces;
}

void Logger::log(const Sev severity, const std::string& message)
{
  if(this->verbosity == LogVerbosity::NONE)
  {
    return;
  }
  
  std::stringstream prefix;
  const auto t = std::time(nullptr);
  const auto tm = *std::localtime(&t);
  
  switch(this->stamping)
  {
    case LogStamping::NONE:
    {
      break;
    }
    case LogStamping::TIMESTAMPS:
    {
      prefix << std::put_time(&tm, "[%H:%M.%S]");
      break;
    }

    case LogStamping::TIMESTAMPSANDDATES:
    {
      prefix << std::put_time(&tm, "[%d-%m-%Y %H:%M.%S]");
      break;
    }
  }
  
  switch(severity)
  {
    case Severity::INFO:
    {
      if(this->verbosity == LogVerbosity::HIGH)
      {
        this->buf.push_back(prefix.str() + " " + message);
      }
      break;
    }
    
    case Severity::WARNING:
    {
      if(this->verbosity == LogVerbosity::MED || this->verbosity == LogVerbosity::HIGH)
      {
        this->buf.push_back(prefix.str() + " [WARNING]: " + message);
      }
      break;
    }

    case Severity::ERR:
    {
      if(this->verbosity == LogVerbosity::HIGH || this->verbosity == LogVerbosity::MED)
      {
        this->buf.push_back(prefix.str() + " [ERROR]: " + message);
      }
      break;
    }

    case Severity::FATAL:
    {
      if(this->verbosity == LogVerbosity::HIGH || this->verbosity == LogVerbosity::MED || this->verbosity == LogVerbosity::LOW)
      {
        this->buf.push_back(prefix.str() + " [FATAL]: " + message);
      }
      break;
    }
  }
  if(this->autoFlush)
  {
    this->flush();
  }
}

void Logger::flush()
{
  switch(this->target)
  {
    case LogTarget::STDOUT:
    {
      for(const auto& message : this->buf)
      {
        fprintf(stdout, "%s\n", message.data());
      }
      
      fflush(stdout);
      break;
    }
    
    case LogTarget::FILE:
    {
      for(const auto& message : this->buf)
      {
        fprintf(this->out, "%s\n", message.data());
      }
      fflush(this->out);
      break;
    }

    case LogTarget::BOTH:
    {
      for(const auto& message : this->buf)
      {
        fprintf(stdout, "%s\n", message.data());
        fprintf(this->out, "%s\n", message.data());
      }
      fflush(stdout);
      fflush(this->out);
      break;
    }
  }
  this->buf.clear();
}
