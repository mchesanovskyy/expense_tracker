// ReSharper disable CppInconsistentNaming
// ReSharper disable CppClangTidyClangDiagnosticExitTimeDestructors
#pragma once
#include <iomanip>
#include <ctime>
#include <sstream>


namespace date_time_helpers
{
	namespace formats
	{
		static string TIME_FORMAT = "%H:%M:%S";
		static string SHORT_TIME_FORMAT = "%H:%M";
		static string DATE_FORMAT = "%Y-%m-%d";
		static string DATE1_FORMAT = "%d-%m-%Y";
		static string S_DATE_TIME_FORMAT = "%Y-%m-%dT%H:%M:%S";
		static string S_DATE_TIME1_FORMAT = "%Y-%m-%dT%H:%M";
		static string DATE_TIME_FORMAT = "%Y-%m-%d %H:%M:%S";
		static string DATE_TIME1_FORMAT = "%Y-%m-%d %H:%M";

		static string FORMATS[] = {
			S_DATE_TIME_FORMAT,
			S_DATE_TIME1_FORMAT,
			DATE_TIME_FORMAT,
			DATE_TIME1_FORMAT,
			DATE_FORMAT,
			DATE1_FORMAT,
			TIME_FORMAT,
			SHORT_TIME_FORMAT
		};
	}

	const int DAY_IN_SECONDS = 86400;


	inline string to_string_format(time_t& timestamp, const string& format)
	{
		tm tm{};
		localtime_s(&tm, &timestamp);
		std::stringstream buffer;
		const char* c_format = format.c_str();
		buffer << std::put_time(&tm, c_format);
		return buffer.str();
	}

	inline string to_date_str(time_t& timestamp)
	{
		return to_string_format(timestamp, formats::DATE_FORMAT);
	}

	inline string to_time_str(time_t& timestamp)
	{
		return to_string_format(timestamp, formats::TIME_FORMAT);
	}

	inline string to_date_time_str(time_t& timestamp)
	{
		return to_string_format(timestamp, formats::S_DATE_TIME_FORMAT);
	}

	inline time_t to_epoch(const char* date_time_str, const char* format)
	{
		std::tm tm{};
		tm.tm_isdst = -1;
		std::istringstream ss(date_time_str);
		ss >> std::get_time(&tm, format);

		const std::time_t time = mktime(&tm);
		return time;
	}

	inline time_t to_epoch(const char* date_time_str)
	{
		for (const auto& format : formats::FORMATS)
		{
			const time_t result = to_epoch(date_time_str, format.c_str());
			if (result >= 0)
			{
				return result;
			}
		}
		return -1;
	}

	inline time_t get_date(time_t& timestamp)
	{
		const string date = to_date_str(timestamp);
		return to_epoch(date.c_str());
	}

	inline time_t now()
	{
		return time(0);
	}

	inline time_t today()
	{
		time_t timestamp = now();
		return get_date(timestamp);
	}

	inline time_t tomorrow()
	{
		return today() + DAY_IN_SECONDS;
	}

	inline time_t yesterday()
	{
		return today() - DAY_IN_SECONDS;
	}

	inline time_t to_end_of_day(time_t& timestamp)
	{
		return  get_date(timestamp) + DAY_IN_SECONDS - 1;
	}
}
