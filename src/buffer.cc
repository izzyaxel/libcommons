#include "commons/buffer.hh"

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

Buffer::Buffer(Buffer const &other)
{
	
}

Buffer::Buffer(Buffer &&other)
{
	
}

Buffer::~Buffer()
{
	
}

Buffer& Buffer::operator=(Buffer const &other)
{
	
	return *this;
}

Buffer& Buffer::operator=(Buffer &&other)
{
	
	return *this;
}

bool Buffer::operator==(Buffer const &other)
{
	
	return false; //TODO
}

void Buffer::write(std::vector<uint8_t> const &in)
{
	this->buffer.insert(this->buffer.end(), in.begin(), in.end());
}

void Buffer::write(uint8_t const *in, size_t size)
{
	this->buffer.insert(this->buffer.end(), in, in + size);
}

void Buffer::discard(size_t amt)
{
	this->buffer.erase(this->buffer.begin(), this->buffer.begin() + amt);
}

size_t Buffer::size()
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

void Buffer::push_back(uint8_t val)
{
	this->buffer.push_back(val);
}

void Buffer::resize(size_t size)
{
	this->buffer.resize(size);
}

void Buffer::transferTo(Buffer &buffer)
{
	buffer.write(this->buffer);
	this->buffer.clear();
}
