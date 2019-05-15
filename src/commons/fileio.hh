#pragma once

#include <string>
#include <vector>

/// Quick and dirty way to read a text file into a string
/// \param filePath 
/// \return 
std::string readTextFile(std::string const &filePath);

/// Quick and dirty way to read a file into a vector of bytes
/// \param filePath 
/// \return 
std::vector<uint8_t> readFile(std::string const &filePath);

/// 
/// \param folderPath 
void createDirectory(std::string const &folderPath);

/// 
/// \param file 
void closeFile(FILE *&file);

/// 
/// \param name 
/// \param mode 
/// \return 
FILE *openFile(std::string const &name, std::string const &mode);

/// Continues reading until a timeout condition has been met or the data has successfully been read
/// \param file 
/// \param destBuffer 
/// \param amount 
void readFile(FILE *file, void *destBuffer, size_t amount, size_t acceptableTimeouts = 10);

/// Continues writing until a timeout condition has been met or the data has successfully been written
/// \param file 
/// \param inputBuffer 
/// \param amount 
void writeFile(FILE *file, void const *inputBuffer, size_t amount, size_t acceptableTimeouts = 10);
