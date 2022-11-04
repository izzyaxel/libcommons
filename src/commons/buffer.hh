#pragma once

#include "serialization.hh"
#include "export.hh"

#include <vector>
#include <cstdint>

struct Buffer : public Serializable //TODO finish buffer
{
	EXPORT void serialize(Serializer &serializer) override;
	EXPORT void deserialize(Serializer &serializer) override;
	
	using iterator = uint8_t *;
	using const_iterator = uint8_t const*;
	
	EXPORT Buffer();
	EXPORT Buffer(const_iterator begin, const_iterator end);
	EXPORT Buffer(Buffer const &other);
	EXPORT Buffer(Buffer &&other);
	EXPORT ~Buffer();
	
	EXPORT Buffer& operator =(Buffer const &other);
	EXPORT Buffer& operator =(Buffer &&other) ;
	EXPORT bool operator ==(Buffer const &other);
	
	[[nodiscard]] EXPORT inline iterator begin() { return nullptr; } //TODO
	[[nodiscard]] EXPORT inline iterator end() { return nullptr; }
	[[nodiscard]] EXPORT inline const_iterator begin() const { return nullptr; }
	[[nodiscard]] EXPORT inline const_iterator end() const { return nullptr; }
	
	EXPORT void write(std::vector<uint8_t> const &in);
	EXPORT void write(uint8_t const *in, size_t size);
	EXPORT void discard(size_t amt);
	[[nodiscard]] EXPORT size_t size();
	[[nodiscard]] EXPORT uint8_t const *data() const;
	[[nodiscard]] EXPORT uint8_t *data();
	EXPORT void push_back(uint8_t val);
	EXPORT void resize(size_t size);
	EXPORT void transferTo(Buffer &buffer);
	
	private:
	std::vector<uint8_t> buffer;
};
