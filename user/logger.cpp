#include "pch-il2cpp.h"
#include "logger.h"
#include <sstream>
#include <iostream>
#include "utility.h"

AUMLogger Log;

void AUMLogger::Create()
{
	auto path = getModulePath(NULL);
	auto logPath = path.parent_path() / "aum-log.txt";
	if (std::filesystem::exists(logPath)) {
		std::filesystem::remove(logPath);
	}

	this->filePath = logPath;
}

void AUMLogger::Write(std::string verbosity, std::string source, std::string message)
{
	std::stringstream ss;
	ss << "[" << verbosity << " - " << source << "] " << message << std::endl;
	std::cout << ss.str();

	std::ofstream file(this->filePath, std::ios_base::app);
	file << ss.str();
	file.close();
}

void AUMLogger::Debug(std::string source, std::string message)
{
	Write("DEBUG", source, message);
}

void AUMLogger::Error(std::string source, std::string message)
{
	Write("ERROR", source, message);
}

void AUMLogger::Info(std::string source, std::string message)
{
	Write("INFO", source, message);
}

void AUMLogger::Debug(std::string message)
{
	Debug("AUM", message);
}

void AUMLogger::Error(std::string message)
{
	Error("AUM", message);
}

void AUMLogger::Info(std::string message)
{
	Info("AUM", message);
}