#include "pch-il2cpp.h"
#include "logger.h"
#include <sstream>
#include <iostream>
#include "main.h"
#include "utility.h"
#include "gitparams.h"

Logger Log;

void Logger::Create()
{
	auto path = getModulePath(NULL);
	auto logPath = path.parent_path() / "aum-log.txt";
	if (std::filesystem::exists(logPath)) {
		std::filesystem::remove(logPath);
	}

	std::ofstream file(logPath);
	std::stringstream ss;

	ss << "AmongUsMenu - " << __TIME__ << " - " << __DATE__ << "\n"; // Log amongusmenu info
	ss << "Commit: " << GetGitCommit() << " - " << GetGitBranch() << "\n"; // Log git info
	ss << "Among Us Version: " << getGameVersion() << "\n"; // Log among us info

	std::cout << ss.str();
	file << ss.str();
	file.close();

	this->filePath = logPath;
}

void Logger::Write(std::string verbosity, std::string source, std::string message)
{
	std::stringstream ss;
	ss << "[" << verbosity << " - " << source << "] " << message << "\n";
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