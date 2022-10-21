#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <assert.h>

class AUMLogger {
public:
	void Create();
	void Write(std::string_view verbosity, std::string_view source, std::string_view message);

	void Debug(std::string_view source, std::string_view message);
	void Error(std::string_view source, std::string_view message);
	void Info(std::string_view source, std::string_view message);
	void Debug(std::string_view message);
	void Error(std::string_view message);
	void Info(std::string_view message);
private:
	std::filesystem::path filePath;
	std::string currentVerbosity;
};
#define _log_source (std::string() + "AUM - " + __func__)

#define LOG_INFO(x) Log.Info(_log_source, x)
#define LOG_DEBUG(x) Log.Debug(_log_source, x)
#define LOG_ERROR(x) Log.Error(_log_source, x)

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

#define LOG_ASSERT(EXPR) \
	if (!(EXPR)) { \
		STREAM_ERROR("(" << #EXPR << ") Assert failed."); \
		assert(EXPR); \
		exit(1); \
	}

extern AUMLogger Log;