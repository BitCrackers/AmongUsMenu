#pragma once
#include <string>
#include <filesystem>
#include <fstream>

class Logger {
public:
	void Create();
	void Write(std::string verbosity, std::string source, std::string message);

	void Debug(std::string source, std::string message);
	void Error(std::string source, std::string message);
	void Info(std::string source, std::string message);
	void Debug(std::string message);
	void Error(std::string message);
	void Info(std::string message);
private:
	std::filesystem::path filePath;
	std::string currentVerbosity;
};

extern Logger Log;