#pragma once

#include <vector>
#include <cstdint>
#include <cstring>

enum struct SeekPos
{
	BEG, CUR, END
};

/// Wrapper for a read-only in-memory buffer
template <typename T> struct DataBuffer
{
	DataBuffer() = delete;
	inline explicit DataBuffer(std::vector<T> const &buffer)
	{
		size_t convSize = sizeof(T) * buffer.size();
		uint8_t const *tmp = reinterpret_cast<uint8_t const *>(buffer.data());
		this->buffer = {tmp, tmp + convSize};
	}
	DataBuffer(T const *src, size_t size)
	{
		size_t convSize = sizeof(T) * size;
		uint8_t const *tmp = reinterpret_cast<uint8_t const *>(src);
		this->buffer = {tmp, tmp + convSize};
	}
	
	size_t read(void *dst, size_t amt)
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
	
	inline void rewind()
	{
		this->pos = 0;
	}
	
	inline bool seek(size_t amt, SeekPos seekPos)
	{
		switch(seekPos)
		{
			case SeekPos::BEG:
				if(amt <= this->buffer.size())
				{
					this->pos = amt;
					return true;
				}
				return false;
			case SeekPos::CUR:
				if(this->pos + amt <= this->buffer.size())
				{
					this->pos += amt;
					return true;
				}
				return false;
			case SeekPos::END:
				if(this->buffer.size() - amt >= 0)
				{
					this->pos = this->buffer.size() - amt;
					return true;
				}
				return false;
		}
		return false;
	}
	
	inline size_t tell()
	{
		return this->pos;
	}
	
private:
	size_t pos = 0;
	std::vector<uint8_t> buffer{};
	
	inline void sanity()
	{
		if(this->pos > this->buffer.size()) this->pos = this->buffer.size();
	}
};
