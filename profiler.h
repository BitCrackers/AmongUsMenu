#pragma once

#include <map>
#include <sstream>
#include <string>

class Profiler
{
public:
	static void InitProfiling();
	static void BeginSample(const char* Stat_Name);
	static void EndSample(const char* Stat_Name);
	static void GetStat(const char* Stat_Name, __int64& AverageSample_Microseconds, __int64& LongestSample_Microseconds, __int64& TotalSamples);
	static const char* GetFormattedStatString(const char* Stat_Name);
	static const wchar_t* GetFormattedStatStringWide(const char* Stat_Name);
	static void AppendStatStringStream(const char* Stat_Name, std::stringstream& ss);
	static void AppendStatStringStreamWide(const char* Stat_Name, std::wstringstream& wss);
	static void WriteStatsToStream(std::stringstream& ss);
	static void WriteStatsToStreamWide(std::wstringstream& wss);
	static void ClearStat(const char* Stat_Name);
	static void ClearStats();

	static bool HasInitialized;

private:
	struct StatObject
	{
		__int64 AverageSample_Microseconds = 0;
		__int64 LongestSample_Microseconds = 0;
		__int64 TotalSamples = 0;
		// 
		LARGE_INTEGER QPCStart, QPCEnd;
		__int64 CumulativeTotal = 0;
		__int64 ElapsedMicroseconds = 0;
	};
	Profiler() {};
	static LARGE_INTEGER QPCFrequency;
	static std::map<std::string, StatObject> StatMap;
};