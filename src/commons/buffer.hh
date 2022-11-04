#pragma once

#include "serialization.hh"
#include "export.hh"

#include <vector>
#include <cstdint>

struct Buffer : public Serializable //TODO finish buffer
{
	COMMONSAPI void serialize(Serializer &serializer) override;
	COMMONSAPI void deserialize(Serializer &serializer) override;
	
	using iterator = uint8_t *;
	using const_iterator = uint8_t const*;
	
	COMMONSAPI Buffer();
	COMMONSAPI Buffer(const_iterator begin, const_iterator end);
	COMMONSAPI Buffer(Buffer const &other);
	COMMONSAPI Buffer(Buffer &&other);
	COMMONSAPI ~Buffer();
	
	COMMONSAPI Buffer& operator =(Buffer const &other);
	COMMONSAPI Buffer& operator =(Buffer &&other) ;
	COMMONSAPI bool operator ==(Buffer const &other);
	
	[[nodiscard]] COMMONSAPI inline iterator begin() { return nullptr; } //TODO
	[[nodiscard]] COMMONSAPI inline iterator end() { return nullptr; }
	[[nodiscard]] COMMONSAPI inline const_iterator begin() const { return nullptr; }
	[[nodiscard]] COMMONSAPI inline const_iterator end() const { return nullptr; }
	
	COMMONSAPI void write(std::vector<uint8_t> const &in);
	COMMONSAPI void write(uint8_t const *in, size_t size);
	COMMONSAPI void discard(size_t amt);
	[[nodiscard]] COMMONSAPI size_t size();
	[[nodiscard]] COMMONSAPI uint8_t const *data() const;
	[[nodiscard]] COMMONSAPI uint8_t *data();
	COMMONSAPI void push_back(uint8_t val);
	COMMONSAPI void resize(size_t size);
	COMMONSAPI void transferTo(Buffer &buffer);
	
	private:
	std::vector<uint8_t> buffer;
};
