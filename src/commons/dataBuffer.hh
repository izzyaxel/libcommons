#pragma once

#include <vector>
#include <cstdint>

enum struct SeekPos
{
	BEG, CUR, END
};

/// Wrapper for a read-only in-memory buffer
template <typename T> struct DataBuffer
{
	DataBuffer() = delete;
	explicit DataBuffer(std::vector<uint8_t> const &buffer) : buffer(buffer) {}
	explicit DataBuffer(std::vector<T> const &buffer)
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
	
	template <typename F> size_t read(F *dst, size_t amt)
	{
		this->sanity();
		size_t convAmt = sizeof(F) * amt;
		if(this->pos + convAmt > this->buffer.size())
		{
			size_t modAmt = this->buffer.size() - (this->pos + convAmt);
			memcpy(dst, this->buffer.data(), modAmt);
			this->pos += modAmt;
			return modAmt / sizeof(F);
		}
		memcpy(dst, this->buffer.data(), convAmt);
		this->pos += convAmt;
		return amt;
	}
	
	void rewind()
	{
		this->pos = 0;
	}
	
	bool seek(size_t amt, SeekPos seekPos)
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
	}
	
private:
	size_t pos = 0;
	std::vector<uint8_t> buffer{};
	
	void sanity()
	{
		if(this->pos > this->buffer.size()) this->pos = this->buffer.size();
	}
};
