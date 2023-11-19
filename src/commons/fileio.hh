#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include "export.hh"

/// Quick and dirty way to read a text file into a string
/// \param filePath 
/// \return 
[[nodiscard]] COMMONS_API std::string readTextFile(std::string const &filePath);

/// Quick and dirty way to read a file into a vector of bytes
/// \param filePath 
/// \return 
[[nodiscard]] COMMONS_API std::vector<uint8_t> readFile(std::string const &filePath);

/// 
/// \param folderPath 
COMMONS_API void createDirectory(std::string const &folderPath);

/// 
/// \param file 
COMMONS_API void closeFile(FILE* &file);

/// 
/// \param name 
/// \param mode 
/// \return 
[[nodiscard]] COMMONS_API FILE* openFile(std::string const &name, std::string const &mode);

/// Continues reading until a timeout condition has been met or the data has successfully been read
/// \param file 
/// \param destBuffer 
/// \param amount 
COMMONS_API size_t readFile(FILE* file, void* destBuffer, size_t amount, size_t acceptableTimeouts = 10);

/// Continues writing until a timeout condition has been met or the data has successfully been written
/// \param file 
/// \param inputBuffer 
/// \param amount 
COMMONS_API size_t writeFile(FILE* file, void const* inputBuffer, size_t amount, size_t acceptableTimeouts = 10);
