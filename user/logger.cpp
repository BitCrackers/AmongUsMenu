#include "pch-il2cpp.h"
#include "logger.h"
#include <sstream>
#include <iostream>
#include "utility.h"

Logger Log;

void Logger::Create()
{
	auto path = getModulePath(NULL);
	auto logPath = path.parent_path() / "aum-log.txt";
	if (std::filesystem::exists(logPath)) {
		std::filesystem::remove(logPath);
	}

	this->filePath = logPath;
}

void Logger::Write(std::string verbosity, std::string source, std::string message)
{
	std::stringstream ss;
	ss << "[" << verbosity << " - " << source << "] " << message << std::endl;
	std::cout << ss.str();

	std::ofstream file(this->filePath, std::ios_base::app);
	file << ss.str();
	file.close();
}

void Logger::Debug(std::string source, std::string message)
{
	Write("DEBUG", source, message);
}

void Logger::Error(std::string source, std::string message)
{
	Write("ERROR", source, message);
}

void Logger::Info(std::string source, std::string message)
{
	Write("INFO", source, message);
}

void Logger::Debug(std::string message)
{
	Debug("AUM", message);
}

void Logger::Error(std::string message)
{
	Error("AUM", message);
}

void Logger::Info(std::string message)
{
	Info("AUM", message);
}