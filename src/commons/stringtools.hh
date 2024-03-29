#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include "export.hh"

/// Check if the given string contains the given token
[[nodiscard]] COMMONS_API bool contains(std::string const &input, std::string const &searchToken);

/// Check if the given string starts with the given token
[[nodiscard]] COMMONS_API bool startsWith(std::string const &input, std::string const &searchToken);

/// Check if the given string ends with the given token
[[nodiscard]] COMMONS_API bool endsWith(std::string const &input, std::string const &searchToken);

/// Cut characters off either end of a string
[[nodiscard]] COMMONS_API std::string subString(std::string const &input, uint32_t const &distFromStart, uint32_t const &distFromEnd);

/// Trim leading and trailing whitespace
[[nodiscard]] COMMONS_API std::string trim(std::string const &input);

/// Remove all occurences of the given character from the input string
[[nodiscard]] COMMONS_API std::string remove(std::string const &input, char const &remove);

/// Remove all occurences of any of the given characters from the input string
[[nodiscard]] COMMONS_API std::string removeMult(std::string const &input, std::vector<char> const &remove);

/// Split a string on the given character
[[nodiscard]] COMMONS_API std::vector<std::string> split(std::string const &input, char const &splitOn, bool const removeMatches);

/// Split a string on any of the given characters
[[nodiscard]] COMMONS_API std::vector<std::string> splitMult(std::string const &input, std::vector<char> const &splitOn, bool const removeMatches);

/// Split a string on the given word
[[nodiscard]] COMMONS_API std::vector<std::string> splitSeq(std::string const &input, std::string const &splitOn, bool const removeMatches);

/// Split a string on any of the given words
[[nodiscard]] COMMONS_API std::vector<std::string> splitSeqMult(std::string const &input, std::vector<std::string> const &splitOn, bool const removeMatches);

/// Replace all instances of a character with another
[[nodiscard]] COMMONS_API std::string replaceAll(std::string const &input, char const &searchFor, char const &replaceWith);

/// Replace all sequences of characters with another
[[nodiscard]] COMMONS_API std::string replaceSeq(std::string const &input, std::string const &search, std::string const &replace);
