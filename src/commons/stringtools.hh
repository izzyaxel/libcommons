#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include "export.hh"

/// Check if the given string contains the given token
[[nodiscard]] COMMONS_API bool contains(const std::string& input, const std::string& searchToken);

/// Check if the given string starts with the given token
[[nodiscard]] COMMONS_API bool startsWith(const std::string& input, const std::string& searchToken);

/// Check if the given string ends with the given token
[[nodiscard]] COMMONS_API bool endsWith(const std::string& input, const std::string& searchToken);

/// Cut characters off either end of a string
[[nodiscard]] COMMONS_API std::string subString(const std::string& input, uint32_t distFromStart, uint32_t distFromEnd);

/// Trim leading and trailing whitespace
[[nodiscard]] COMMONS_API std::string trim(const std::string& input);

/// Remove all occurences of the given character from the input string
[[nodiscard]] COMMONS_API std::string remove(const std::string& input, char remove);

/// Remove all occurences of any of the given characters from the input string
[[nodiscard]] COMMONS_API std::string removeMult(const std::string& input, const std::vector<char>& remove);

/// Split a string on the given character
[[nodiscard]] COMMONS_API std::vector<std::string> split(const std::string& input, char splitOn, bool removeMatches);

/// Split a string on any of the given characters
[[nodiscard]] COMMONS_API std::vector<std::string> splitMult(const std::string& input, const std::vector<char>& splitOn, bool removeMatches);

/// Split a string on the given word
[[nodiscard]] COMMONS_API std::vector<std::string> splitSeq(const std::string& input, const std::string& splitOn, bool removeMatches);

/// Split a string on any of the given words
[[nodiscard]] COMMONS_API std::vector<std::string> splitSeqMult(const std::string& input, const std::vector<std::string>& splitOn, bool removeMatches);

/// Replace all instances of a character with another
[[nodiscard]] COMMONS_API std::string replaceAll(const std::string& input, char searchFor, char replaceWith);

/// Replace all sequences of characters with another
[[nodiscard]] COMMONS_API std::string replaceSeq(const std::string& input, const std::string& search, const std::string& replace);
