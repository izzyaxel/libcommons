#pragma once

#include "vec2.hh"

#include <vector>
#include <ctgmath>

/// PI constant
template<typename T> T constexpr pi = (T)3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145649L;

template<typename T> int32_t sign(T in)
{
	return (in > (T)0) - (in < (T)0);
}

/// Find a point along a sine wave between a min and max value
template<typename T> T boundedSine(T max, T min, T time)
{
	return ((max - min) * std::sin(time) + max + min) / (T)2;
}

/// Convert a degree angle into a radian angle
template<typename T> T degToRad(T degree)
{
	return degree * (pi<T> / (T)180);
}

/// Convert a radian angle into a degree angle
template<typename T> T radToDeg(T radian)
{
	return radian / (pi<T> / (T)180);
}

template<typename T> T distance(vec2<T> const &a, vec2<T> const &b)
{
	return (T)std::sqrt(std::pow(b.x() - a.x(), 2) + std::pow(b.y() - a.y(), 2));
}

/// A pascal triangle, typically used for finding weights, eg for blurring algorithms
template<typename T> struct PascalTriangle
{
	std::vector<std::vector<T>> rows{{1}};
	
	inline explicit PascalTriangle(size_t rows)
	{
		for (size_t i = 1; i < rows + 1; i++) generateRow();
	}
	
	std::vector<T> const &row(size_t row)
	{
		for (size_t i = rows.size(); i < row + 1; i++) generateRow();
		return rows[row];
	}

protected:
	inline void generateRow()
	{
		auto &lastRow = rows.back();
		std::vector<T> newRow{(T)1};
		newRow.resize(rows.size());
		for (size_t i = 1; i < rows.size(); i++) newRow[i] = lastRow[i - 1] + lastRow[i];
		newRow.push_back((T)1);
		rows.push_back(newRow);
	}
};
