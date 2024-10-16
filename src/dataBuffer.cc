#include "commons/dataBuffer.hh"

template <typename T> size_t DataBuffer<T>::read(void* dst, const size_t amt)
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

template <typename T> void DataBuffer<T>::rewind()
{
  this->pos = 0;
}

template <typename T> bool DataBuffer<T>::seek(const size_t amt, const SeekPos seekPos)
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
      if(this->buffer.size() - amt >= 0)
      {
        this->pos = this->buffer.size() - amt;
        return true;
      }
      return false;
    }
  }
  return false;
}

template <typename T> size_t DataBuffer<T>::tell() const
{
  return this->pos;
}

template <typename T> void DataBuffer<T>::sanity()
{
  if(this->pos > this->buffer.size()) this->pos = this->buffer.size();
}
