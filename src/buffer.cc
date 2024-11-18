#include "commons/buffer.hh"

//TODO write Buffer
void Buffer::serialize(Serializer &serializer)
{
  
}

void Buffer::deserialize(Serializer &serializer)
{
  
}

Buffer::Buffer()
{
  
}

Buffer::Buffer(Buffer::const_iterator begin, Buffer::const_iterator end)
{
  
}

Buffer::Buffer(const Buffer& other)
{
  
}

Buffer::Buffer(Buffer&& other)
{
  
}

Buffer& Buffer::operator=(const Buffer& other)
{
  return *this;
}

Buffer& Buffer::operator=(Buffer&& other)
{
  return *this;
}

bool Buffer::operator==(const Buffer& other)
{
  return false;
}

Buffer::iterator Buffer::begin()
{
  return nullptr;
}
  
Buffer::iterator Buffer::end()
{
  return nullptr;
}
  
Buffer::const_iterator Buffer::begin() const
{
  return nullptr;
}
  
Buffer::const_iterator Buffer::end() const
{
  return nullptr;
}

void Buffer::write(const std::vector<uint8_t>& in)
{
  this->buffer.insert(this->buffer.end(), in.begin(), in.end());
}

void Buffer::write(const uint8_t* in, const size_t size)
{
  this->buffer.insert(this->buffer.end(), in, in + size);
}

void Buffer::discard(const size_t amt)
{
  this->buffer.erase(this->buffer.begin(), this->buffer.begin() + (long long)amt);
}

size_t Buffer::size() const
{
  return this->buffer.size();
}

uint8_t const* Buffer::data() const
{
  return this->buffer.data();
}

uint8_t* Buffer::data()
{
  return this->buffer.data();
}

void Buffer::push_back(const uint8_t val)
{
  this->buffer.push_back(val);
}

void Buffer::resize(const size_t size)
{
  this->buffer.resize(size);
}

void Buffer::transferTo(Buffer& buffer)
{
  buffer.write(this->buffer);
  this->buffer.clear();
}
