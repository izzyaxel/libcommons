#pragma once

#include <cstdint>
#include <cmath>

//Fixed point number
template <uint32_t bits, typename V> struct fixed
{
	static_assert(!std::is_floating_point<V>() && bits <= sizeof(V) * 8);
	
	#if defined(__MINGW32__) || defined(__clang__)
	using int128_t = __int128_t;
	using uint128_t = __uint128_t;
	#elif defined(__MSC_VER)
	using int128_t = __int128;
	using uint128_t = __uint128;
	#endif
	
	fixed() = default;
	constexpr fixed<bits, V>& operator =(fixed<bits, V> const &other) = default;
	constexpr fixed<bits, V>& operator =(fixed<bits, V> &&other) = default;
	constexpr fixed<bits, V>(fixed<bits, V> const &other) = default;
	constexpr fixed<bits, V>(fixed<bits, V> &&other) = default;
	
	constexpr inline fixed(float val) : val(std::round(val * this->scale)) {}
	constexpr inline fixed(double val) : val(std::round(val * this->scale)) {}
	constexpr inline fixed(uint8_t val) : val(val * this->scale) {}
	constexpr inline fixed(uint16_t val) : val(val * this->scale) {}
	constexpr inline fixed(uint32_t val) : val(val * this->scale) {}
	constexpr inline fixed(uint64_t val) : val(val * this->scale) {}
	constexpr inline fixed(int8_t val) : val(val * this->scale) {}
	constexpr inline fixed(int16_t val) : val(val * this->scale) {}
	constexpr inline fixed(int32_t val) : val(val * this->scale) {}
	constexpr inline fixed(int64_t val) : val(val * this->scale) {}
	
	//Conversion
	constexpr explicit inline operator float() const
	{
		return this->toFloat();
	}
	
	constexpr explicit inline operator double() const
	{
		return this->toDouble();
	}
	
	//Bool
	constexpr inline operator bool() const
	{
		return this->val != 0;
	}
	
	//Comparison
	/*template <uint32_t obits, typename T> constexpr bool operator ==(fixed<obits, T> other) const
	{
		if(bits != obits)
		{
			fixed<bits, T> conv = other.changeBits<bits>(); //FIXME wot??
			return this->val == conv.val;
		}
		return this->val == other.val;
	}
	
	template <uint32_t obits, typename T> constexpr inline bool operator !=(fixed<obits, T> other) const
	{
		return !this->operator==(other);
	}
	
	template <uint32_t obits, typename T> constexpr inline bool operator <(fixed<obits, T> other) const
	{
		if(bits != obits)
		{
			fixed<bits, T> conv = other.changeBits<bits>();
			return this->val < conv.val;
		}
		return this->val < other.val;
	}
	
	template <uint32_t obits, typename T> constexpr inline bool operator >(fixed<obits, T> other) const
	{
		if(bits != obits)
		{
			fixed<bits, T> conv = other.changeBits<bits>();
			return this->val > conv.val;
		}
		return this->val > other.val;
	}
	
	template <uint32_t obits, typename T> constexpr inline bool operator <=(fixed<obits, T> other) const
	{
		if(bits != obits)
		{
			fixed<bits, T> conv = other.changeBits<bits>();
			return this->val <= conv.val;
		}
		return this->val <= other.val;
	}
	
	template <uint32_t obits, typename T> constexpr inline bool operator >=(fixed<obits, T> other) const
	{
		if(bits != obits)
		{
			fixed<bits, T> conv = other.changeBits<bits>();
			return this->val >= conv.val;
		}
		return this->val >= other.val;
	}*/
	
	//Math operators
	constexpr inline fixed<bits, V> operator -()
	{
		this->val = -this->val;
		return *this;
	}
	
	 //Self
	constexpr inline fixed<bits, V> operator +(fixed<bits, V> other) const
	{
		fixed<bits, V> out{};
		out.val = this->val + other.val;
		return out;
	}
	constexpr inline fixed<bits, V> operator -(fixed<bits, V> other) const
	{
		fixed<bits, V> out{};
		out.val = this->val - other.val;
		return out;
	}
	constexpr inline fixed<bits, V> operator *(fixed<bits, V> other) const
	{
		fixed<bits, V> out{};
		out.val = ((int128_t)this->val * (int128_t)other.val) / this->scale;
		return out;
	}
	constexpr inline fixed<bits, V> operator /(fixed<bits, V> other) const
	{
		fixed<bits, V> out{};
		out.val = ((int128_t)this->val * this->scale) / (int128_t)other.val;
		return out;
	}
	constexpr inline fixed<bits, V> operator %(fixed<bits, V> other) const
	{
		fixed<bits, V> out{};
		out.val = this->val % other.val;
		return out;
	}
	
	 //Self compound
	constexpr inline fixed<bits, V> operator +=(fixed<bits, V> other)
	{
		this->val = this->val + other.val;
		return *this;
	}
	constexpr inline fixed<bits, V> operator -=(fixed<bits, V> other)
	{
		this->val = this->val - other.val;
		return *this;
	}
	constexpr inline fixed<bits, V> operator *=(fixed<bits, V> other)
	{
		this->val = ((int128_t)this->val * (int128_t)other.val) / this->scale;
		return *this;
	}
	constexpr inline fixed<bits, V> operator /=(fixed<bits, V> other)
	{
		this->val = ((int128_t)this->val * this->scale) / (int128_t)other.val;
		return *this;
	}
	constexpr inline fixed<bits, V> operator %=(fixed<bits, V> other)
	{
		this->val = this->val % other.val;
		return *this;
	}
	
	 //Value
	template <typename T> constexpr fixed<bits, V> operator +(T other) const
	{
		static_assert(std::is_integral<T>() || std::is_floating_point<T>());
		fixed<bits, V> out{};
		out.val = this->val + (V)std::round(other * this->scale);
		return out;
	}
	template <typename T> constexpr fixed<bits, V> operator -(T other) const
	{
		static_assert(std::is_integral<T>() || std::is_floating_point<T>());
		fixed<bits, V> out{};
		out.val = this->val - (V)std::round(other * this->scale);
		return out;
	}
	template <typename T> constexpr fixed<bits, V> operator *(T other) const
	{
		static_assert(std::is_integral<T>() || std::is_floating_point<T>());
		fixed<bits, V> out{};
		out.val = ((int128_t)this->val * (int128_t)std::round(other * this->scale)) / this->scale;
		return out;
	}
	template <typename T> constexpr fixed<bits, V> operator /(T other) const
	{
		static_assert(std::is_integral<T>() || std::is_floating_point<T>());
		fixed<bits, V> out{};
		out.val = ((int128_t)this->val * this->scale) / (int128_t)std::round(other * this->scale);
		return out;
	}
	template <typename T> constexpr fixed<bits, V> operator %(T other) const
	{
		static_assert(std::is_integral<T>() || std::is_floating_point<T>());
		fixed<bits, V> out{};
		out.val = this->val % (V)std::round(other * this->scale);
		return out;
	}
	
	 //Value compound
	template <typename T> constexpr fixed<bits, V> operator +=(T other)
	{
		static_assert(std::is_integral<T>() || std::is_floating_point<T>());
		this->val = this->val + (T)std::round(other * this->scale);
		return *this;
	}
	template <typename T> constexpr fixed<bits, V> operator -=(T other)
	{
		static_assert(std::is_integral<T>() || std::is_floating_point<T>());
		this->val = this->val - (T)std::round(other * this->scale);
		return *this;
	}
	template <typename T> constexpr fixed<bits, V> operator *=(T other)
	{
		static_assert(std::is_integral<T>() || std::is_floating_point<T>());
		this->val = ((int128_t)this->val * (int128_t)std::round(other * this->scale)) / this->scale;
		return *this;
	}
	template <typename T> constexpr fixed<bits, V> operator /=(T other)
	{
		static_assert(std::is_integral<T>() || std::is_floating_point<T>());
		this->val = ((int128_t)this->val * this->scale) / (int128_t)std::round(other * this->scale);
		return *this;
	}
	template <typename T> constexpr fixed<bits, V> operator %=(T other)
	{
		static_assert(std::is_integral<T>() || std::is_floating_point<T>());
		this->val = this->val % (T)std::round(other * this->scale);
		return *this;
	}
	
	 //Bitwise
	constexpr fixed<bits, V> inline operator ~() const
	{
		fixed<bits, V> out{};
		out.val = ~this->val;
		return out;
	}
	
	constexpr fixed<bits, V> inline operator >>(int32_t other) const
	{
		fixed<bits, V> out{};
		out.val = this->val >> other;
		return out;
	}
	
	constexpr fixed<bits, V> inline operator <<(int32_t other) const
	{
		fixed<bits, V> out{};
		out.val = this->val << other;
		return out;
	}
	
	constexpr fixed<bits, V> inline operator |(int32_t other) const
	{
		fixed<bits, V> out{};
		out.val = this->val | other;
		return out;
	}
	
	constexpr fixed<bits, V> inline operator &(int32_t other) const
	{
		fixed<bits, V> out{};
		out.val = this->val & other;
		return out;
	}
	
	constexpr fixed<bits, V> inline operator ^(int32_t other) const
	{
		fixed<bits, V> out{};
		out.val = this->val ^ other;
		return out;
	}
	
	 //Bitwise compound
	constexpr fixed<bits, V> inline operator <<=(int32_t other)
	{
		this->val = this->val << other;
		return *this;
	}
	
	constexpr fixed<bits, V> inline operator >>=(int32_t other)
	{
		this->val = this->val >> other;
		return *this;
	}
	
	constexpr fixed<bits, V> inline operator |=(int32_t other)
	{
		this->val = this->val | other;
		return *this;
	}
	
	constexpr fixed<bits, V> inline operator &=(int32_t other)
	{
		this->val = this->val & other;
		return *this;
	}
	
	constexpr fixed<bits, V> inline operator ^=(int32_t other)
	{
		this->val = this->val ^ other;
		return *this;
	}
	
	//Outputs
	[[nodiscard]] constexpr inline float toFloat() const
	{
		return ((float)this->val / this->scale);
	}
	
	[[nodiscard]] constexpr inline double toDouble() const
	{
		return ((double)this->val / this->scale);
	}
	
	template <uint32_t nbits> [[nodiscard]] constexpr fixed<nbits, V> changeBits() const
	{
		return fixed<nbits, V>{this->toDouble()};
	}
	
private:
	static constexpr uint128_t const scale = (uint128_t)1 << bits;
	V val;
};
static_assert(std::is_pod<fixed<8, int32_t>>());
