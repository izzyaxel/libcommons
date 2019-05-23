#pragma once

#include "serialization.hh"

#include <vector>
#include <cstdint>

struct Buffer : public Serializable //TODO finish buffer
{
	void serialize(Serializer &serializer) override;
	void deserialize(Serializer &serializer) override;
	
	using iterator = uint8_t *;
	using const_iterator = uint8_t const*;
	
	Buffer();
	Buffer(const_iterator begin, const_iterator end);
	Buffer(Buffer const &other);
	Buffer(Buffer &&other);
	~Buffer();
	
	Buffer& operator =(Buffer const &other);
	Buffer& operator =(Buffer &&other) ;
	bool operator ==(Buffer const &other);
	
	inline iterator begin() { return nullptr; } //TODO
	inline iterator end() { return nullptr; }
	inline const_iterator begin() const { return nullptr; }
	inline const_iterator end() const { return nullptr; }
	
	void write(std::vector<uint8_t> const &in);
	void write(uint8_t const *in, size_t size);
	void discard(size_t amt);
	size_t size();
	uint8_t const *data() const;
	uint8_t *data();
	void push_back(uint8_t val);
	void resize(size_t size);
	void transferTo(Buffer &buffer);
	
	private:
	std::vector<uint8_t> buffer;
};
