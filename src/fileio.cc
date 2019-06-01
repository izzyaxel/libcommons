#include "commons/fileio.hh"

#include <stdexcept>
#include <fstream>

#if defined(WINDOWS)
#include <windows.h>
#include <libloaderapi.h>
#elif defined(LINUX) || defined(OSX)
#include <sys/stat.h>
#include <unistd.h>
#endif

std::string readTextFile(std::string const &filePath)
{
	std::ifstream fileIn;
	fileIn.open(filePath);
	if(!fileIn) printf("Error opening file %s\n", filePath.data());
	return {std::istreambuf_iterator<char>(fileIn), std::istreambuf_iterator<char>()};
}

std::vector<uint8_t> readFile(std::string const &filePath)
{
	FILE *in = fopen(filePath.data(), "rb");
	if(!in)
	{
		printf("File reader: failed to read input file: %s\n", filePath.data());
		return {};
	}
	fseek(in, SEEK_END, SEEK_SET);
	size_t len = (size_t)ftell(in);
	rewind(in);
	std::vector<uint8_t> data;
	data.resize(len);
	fread(data.data(), 1, len, in);
	fclose(in);
	return data;
}

void createDirectory(std::string const &folderPath)
{
	#if defined(WINDOWS)
	CreateDirectory(folderPath.data(), nullptr);
	#elif defined(LINUX) || defined(OSX)
	mkdir(folderPath.data(), 0755);
	#endif
}

void closeFile(FILE *&file)
{
	int result = fclose(file);
	if(result != 0) throw std::runtime_error("Failed to close file");
	file = nullptr;
}

FILE* openFile(std::string const &name, std::string const &mode)
{
	FILE *out = fopen(name.data(), mode.data());
	if(!out) throw std::runtime_error("Failed to open " + name + " with mode " + mode);
	return out;
}

size_t readFile(FILE *file, void *destBuffer, size_t amount, size_t acceptableTimeouts)
{
	size_t amtRead = 0, timeoutCounter = 0, out = 0;
	do
	{
		if(timeoutCounter >= acceptableTimeouts) throw std::runtime_error("Unable to read from file, timed out after " + std::to_string(acceptableTimeouts) + " 0-length reads");
		amtRead = fread(destBuffer, 1, amount - amtRead, file);
		out += amtRead;
		if(amtRead == 0) timeoutCounter++;
	} while(amtRead < amount);
	return out;
}

size_t writeFile(FILE *file, void const *inputBuffer, size_t amount, size_t acceptableTimeouts)
{
	size_t amtWritten = 0, timeoutCounter = 0, out = 0;
	do
	{
		if(timeoutCounter >= acceptableTimeouts) throw std::runtime_error("Unable to write to file, timed out after " + std::to_string(acceptableTimeouts) + " 0-length writes");
		amtWritten = fwrite(inputBuffer, 1, amount - amtWritten, file);
		out += amtWritten;
		if(amtWritten == 0) timeoutCounter++;
	} while(amtWritten < amount);
	return out;
}
