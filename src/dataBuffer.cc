#include "commons/dataBuffer.hh"

DataBuffer::DataBuffer(std::vector<uint8_t> buffer)
{
  this->buffer = std::move(buffer);
}
  
DataBuffer::DataBuffer(const uint8_t* src, const size_t size)
{
  this->buffer = {src, src + size};
}

size_t DataBuffer::read(void* dst, const size_t amt)
{
  this->sanity();
  if(this->pos == this->buffer.size()) return 0;
  if(this->pos + amt > this->buffer.size())
  {
    size_t modAmt = amt - (this->buffer.size() - (this->pos));
    memcpy(dst, this->buffer.data(), modAmt);
    this->pos += modAmt;
    return modAmt;
  }
  memcpy(dst, this->buffer.data() + pos, amt);
  this->pos += amt;
  return amt;
}
  
void DataBuffer::rewind()
{
  this->pos = 0;
}
  
bool DataBuffer::seek(const size_t amt, const SeekPos seekPos)
{
  switch(seekPos)
  {
    case SeekPos::BEG:
    {
      if(amt <= this->buffer.size())
      {
        this->pos = amt;
        return true;
      }
      return false;
    }
    case SeekPos::CUR:
    {
      if(this->pos + amt <= this->buffer.size())
      {
        this->pos += amt;
        return true;
      }
      return false;
    }
    case SeekPos::END:
    {
      if((long long int)this->buffer.size() - (long long int)amt >= 0)
      {
        this->pos = this->buffer.size() - amt;
        return true;
      }
      return false;
    }
  }
  return false;
}
  
size_t DataBuffer::tell() const
{
  return this->pos;
}

uint8_t* DataBuffer::data() const
{
  return this->buffer.data();
}

void DataBuffer::sanity()
{
  if(this->pos > this->buffer.size())
  {
    this->pos = this->buffer.size();
  }
}
