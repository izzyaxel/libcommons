#pragma once

#include <cstdint>
#include <cstring>
#include <vector>
#include <string>

struct Serializer
{
	inline void writeString(std::string const &in)
	{
		this->write<size_t>(in.size());
		this->data.insert(this->data.end(), reinterpret_cast<uint8_t const *>(in.data()), reinterpret_cast<uint8_t const *>(in.data()) + in.size());
	}
	
	template <typename T> inline void writeContainer(T const &in)
	{
		this->write<size_t>(in.size());
		this->data.insert(this->data.end(), reinterpret_cast<uint8_t const *>(in.data()), reinterpret_cast<uint8_t const *>(in.data()) + in.size());
	}
	
	template <typename T, typename = std::enable_if_t<std::is_pod<T>::value && !std::is_pointer<T>::value>> void write(T in)
	{
		this->data.insert(this->data.end(), reinterpret_cast<uint8_t const *>(&in), reinterpret_cast<uint8_t const *>(&in) + sizeof(T));
	}
	
	inline void read(uint8_t *dest, size_t size)
	{
		memcpy(dest, this->data.data() + this->readOffset, size);
		this->readOffset += size;
		this->_size -= size;
	}
	
	inline void readString(std::string &out)
	{
		size_t stringSize = 0;
		this->read<size_t>(stringSize);
		out.resize(stringSize);
		this->read(reinterpret_cast<uint8_t *>(out.data()), stringSize);
	}
	
	template <typename T> void readContainer(T &out)
	{
		size_t containerSize = 0;
		this->read<size_t>(containerSize);
		this->read(reinterpret_cast<uint8_t *>(&out), containerSize);
	}
	
	template <typename T, typename = std::enable_if_t<std::is_pod<T>::value && !std::is_pointer<T>::value>> void read(T &out)
	{
		this->read(reinterpret_cast<uint8_t *>(&out), sizeof(T));
	}
	
	[[nodiscard]] inline size_t size()
	{
		return this->_size;
	}
	
	inline void end()
	{
		this->readOffset = 0;
		this->data.clear();
	}

private:
	size_t _size = 0;
	size_t readOffset = 0;
	std::vector<uint8_t> data;
};

struct Serializable
{
	virtual ~Serializable() = default;
	virtual void serialize(Serializer &serializer) = 0;
	virtual void deserialize(Serializer &serializer) = 0;

protected:
	Serializable() = default;
};
