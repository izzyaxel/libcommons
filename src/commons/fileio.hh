#pragma once

#include <string>
#include <vector>
#include <cstdint>

[[nodiscard]]
auto readTextFile(const std::string& filePath) -> std::string;

[[nodiscard]]
auto readFile(const std::string& filePath) -> std::vector<uint8_t>;

[[nodiscard]]
auto openFile(const std::string& name, const std::string& mode) -> FILE*;

auto createDirectory(const std::string& folderPath) -> void;
auto closeFile(FILE*& file) -> void;
auto readFile(FILE* file, void* destBuffer, size_t amount, size_t acceptableTimeouts = 10) -> size_t;
auto writeFile(FILE* file, const void* inputBuffer, size_t amount, size_t acceptableTimeouts = 10) -> size_t;
