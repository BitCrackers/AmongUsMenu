#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>

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
#define _log_source (std::string() + "AUM - " + __func__)

#define LOG_INFO(x) Log.Info(_log_source, x);
#define LOG_DEBUG(x) Log.Debug(_log_source, x);
#define LOG_ERROR(x) Log.Error(_log_source, x);

#define STREAM_DEBUG(x) \
	do { \
		std::ostringstream ss; \
		ss << x; \
		LOG_DEBUG(ss.str()); \
	} while (0)

#define STREAM_ERROR(x) \
	do { \
		std::ostringstream ss; \
		ss << x; \
		LOG_ERROR(ss.str()); \
	} while (0)

extern Logger Log;