#pragma once

#include <ctgmath>
#include <cstring>

template<typename T> struct vec2
{
	T data[2];
	
	[[nodiscard]] inline T &x()
	{
		return this->data[0];
	}
	[[nodiscard]] inline T &y()
	{
		return this->data[1];
	}
	[[nodiscard]] inline T const &x() const
	{
		return this->data[0];
	}
	[[nodiscard]] inline T const &y() const
	{
		return this->data[1];
	}
	
	// 2-way Swizzling (sort of) 3 permutations
	[[nodiscard]] inline vec2<T> xx() const {return vec2<T>{this->data[0], this->data[0]};}
	[[nodiscard]] inline vec2<T> yy() const {return vec2<T>{this->data[1], this->data[1]};}
	[[nodiscard]] inline vec2<T> yx() const {return vec2<T>{this->data[1], this->data[0]};}
	
	inline constexpr vec2<T>() = default;
	
	template<typename U> constexpr explicit vec2<T>(vec2<U> const &other)
	{
		this->data[0] = other.data[0];
		this->data[1] = other.data[1];
	}
	
	constexpr inline vec2<T>(T x, T y)
	{
		this->data[0] = x;
		this->data[1] = y;
	}
	
	constexpr inline explicit vec2<T>(T const &scalar)
	{
		this->data[0] = scalar;
		this->data[1] = scalar;
	}
	
	inline T &operator[](size_t index)
	{
		return this->data[index];
	}
	
	inline T const &operator[](size_t index) const
	{
		return this->data[index];
	}
	
	inline bool operator==(vec2<T> const &other) const
	{
		return this->data[0] == other[0] && this->data[1] == other[1];
	}
	
	inline bool operator!=(vec2<T> const &other) const
	{
		return this->data[0] != other[0] || this->data[1] != other[1];
	}
	
	inline vec2<T> operator+(vec2<T> const &other) const
	{
		return vec2<T>{this->data[0] + other[0], this->data[1] + other[1]};
	}
	
	inline vec2<T> operator+(T const &scalar) const
	{
		return vec2<T>{(T)(this->data[0] + scalar), (T)(this->data[1] + scalar)};
	}
	
	inline vec2<T> operator-(vec2<T> const &other) const
	{
		return vec2<T>{this->data[0] - other[0], this->data[1] - other[1]};
	}
	
	inline vec2<T> operator-(T const &scalar) const
	{
		return vec2<T>{(T)(this->data[0] - scalar), (T)(this->data[1] - scalar)};
	}
	
	inline vec2<T> operator-() const
	{
		return vec2<T>{-this->data[0], -this->data[1]};
	}
	
	inline vec2<T> operator*(vec2<T> const &other) const
	{
		return vec2<T>{this->data[0] * other[0], this->data[1] * other[1]};
	}
	
	inline vec2<T> operator*(T scalar) const
	{
		return vec2<T>{(T)(this->data[0] * scalar), (T)(this->data[1] * scalar)};
	}
	
	inline vec2<T> operator/(vec2<T> const &other) const
	{
		return vec2<T>{this->data[0] / other[0], this->data[1] / other[1]};
	}
	
	inline vec2<T> operator/(T const &scalar) const
	{
		return vec2<T>{(T)(this->data[0] / scalar), (T)(this->data[1] / scalar)};
	}
	
	inline vec2<T> &operator+=(vec2<T> const &other)
	{
		this->data[0] += other[0];
		this->data[1] += other[1];
		return *this;
	}
	
	inline vec2<T> &operator-=(vec2<T> const &other)
	{
		this->data[0] -= other[0];
		this->data[1] -= other[1];
		return *this;
	}
	
	inline vec2<T> &operator*=(vec2<T> const &other)
	{
		this->data[0] *= other[0];
		this->data[1] *= other[1];
		return *this;
	}
	
	inline vec2<T> &operator/=(vec2<T> const &other)
	{
		this->data[0] /= other[0];
		this->data[1] /= other[1];
		return *this;
	}
	
	inline vec2<T> &operator++()
	{
		this->data[0]++;
		this->data[1]++;
		return *this;
	}
	
	inline vec2<T> const operator++(int)
	{
		vec2<T> out = *this;
		this->data[0]++;
		this->data[1]++;
		return out;
	}
	
	inline vec2<T> &operator--()
	{
		this->data[0]--;
		this->data[1]--;
		return *this;
	}
	
	inline vec2<T> const operator--(int)
	{
		vec2<T> out = *this;
		this->data[0]--;
		this->data[1]--;
		return out;
	}
	
	inline void set(T x, T y)
	{
		this->data[0] = x;
		this->data[1] = y;
	}
	
	inline void setAll(T value)
	{
		this->set(value, value);
	}
	
	inline void floor()
	{
		this->data[0] = (T)std::floor(this->data[0]);
		this->data[1] = (T)std::floor(this->data[1]);
	}
	
	inline void ceil()
	{
		this->data[0] = (T)std::ceil(this->data[0]);
		this->data[1] = (T)std::ceil(this->data[1]);
	}
	
	inline void round()
	{
		this->data[0] = (T)std::round(this->data[0]);
		this->data[1] = (T)std::round(this->data[1]);
	}
	
	inline void invert()
	{
		this->data[0] = -this->data[0];
		this->data[1] = -this->data[1];
	}
	
	[[nodiscard]] inline vec2<T> inverse() const
	{
		return {-this->data[0], -this->data[1]};
	}
	
	[[nodiscard]] inline T mag() const
	{
		return std::sqrt(this->data[0] * this->data[0] + this->data[1] * this->data[1]);
	}
	
	[[nodiscard]] inline T dot(vec2<T> const &b) const
	{
		return this->data[0] * b.x + this->data[1] * b.y;
	}
	
	inline void normalize()
	{
		T length = this->mag();
		this->data[0] /= length;
		this->data[1] /= length;
	}
	
	[[nodiscard]] inline vec2<T> normalized() const
	{
		vec2<T> out;
		T length = this->mag();
		out[0] = this->data[0] / length;
		out[1] = this->data[1] / length;
		return out;
	}
	
	using value_type = T;
	
	[[nodiscard]] inline size_t size() const
	{
		return 2;
	}
	
	[[nodiscard]] inline std::string toString() const
	{
		std::string out = "(vec2)\n[x: ";
		out += std::to_string(this->data[0]);
		out += " y: ";
		out += std::to_string(this->data[1]);
		out += "]\n";
		return out;
	}
	
	inline void print(std::string const &name) const
	{
		printf("%s: %s\n", name.data(), this->toString().data());
	}
};
static_assert(std::is_standard_layout<vec2<int32_t>>() && std::is_trivial<vec2<int32_t>>());
