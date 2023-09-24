#include "pch-il2cpp.h"
#include "logger.h"
#include <sstream>
#include <iostream>
#include "utility.h"

SMAULogger Log;

void SMAULogger::Create()
{
	const auto path = getModulePath(NULL);
	const auto logPath = path.parent_path() / "smau-log.txt";
	const auto prevLogPath = path.parent_path() / "smau-prev-log.txt";

	std::error_code errCode;
	std::filesystem::remove(prevLogPath, errCode);
	std::filesystem::rename(logPath, prevLogPath, errCode);
	std::filesystem::remove(logPath, errCode);

	this->filePath = logPath;
}

void SMAULogger::Write(std::string_view verbosity, std::string_view source, std::string_view message)
{
	std::stringstream ss;
	// FIXME: std::chrono::current_zone requires Windows 10 version 1903/19H1 or later.
	// ss << std::format("[{:%EX}]", std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now()));
	ss << std::format("[{:%EX}]", std::chrono::system_clock::now());
	ss << "[" << verbosity << " - " << source << "] " << message << std::endl;
	std::cout << ss.str();

	std::ofstream file(this->filePath, std::ios_base::app);
	file << ss.str();
	file.close();
}

void SMAULogger::Debug(std::string_view source, std::string_view message)
{
	Write("DEBUG", source, message);
}

void SMAULogger::Error(std::string_view source, std::string_view message)
{
	Write("ERROR", source, message);
}

void SMAULogger::Info(std::string_view source, std::string_view message)
{
	Write("INFO", source, message);
}

void SMAULogger::Debug(std::string_view message)
{
	Debug("SMAU", message);
}

void SMAULogger::Error(std::string_view message)
{
	Error("SMAU", message);
}

void SMAULogger::Info(std::string_view message)
{
	Info("SMAU", message);
}