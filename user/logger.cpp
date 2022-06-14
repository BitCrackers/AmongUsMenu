#include "pch-il2cpp.h"
#include "logger.h"
#include <sstream>
#include <iostream>
#include "utility.h"

AUMLogger Log;

void AUMLogger::Create()
{
	const auto path = getModulePath(NULL);
	const auto logPath = path.parent_path() / "aum-log.txt";
	const auto prevLogPath = path.parent_path() / "aum-prev-log.txt";

	std::error_code errCode;
	std::filesystem::remove(prevLogPath, errCode);
	std::filesystem::rename(logPath, prevLogPath, errCode);
	std::filesystem::remove(logPath, errCode);

	this->filePath = logPath;
}

void AUMLogger::Write(std::string_view verbosity, std::string_view source, std::string_view message)
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

void AUMLogger::Debug(std::string_view source, std::string_view message)
{
	Write("DEBUG", source, message);
}

void AUMLogger::Error(std::string_view source, std::string_view message)
{
	Write("ERROR", source, message);
}

void AUMLogger::Info(std::string_view source, std::string_view message)
{
	Write("INFO", source, message);
}

void AUMLogger::Debug(std::string_view message)
{
	Debug("AUM", message);
}

void AUMLogger::Error(std::string_view message)
{
	Error("AUM", message);
}

void AUMLogger::Info(std::string_view message)
{
	Info("AUM", message);
}