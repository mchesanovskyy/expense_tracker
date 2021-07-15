#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

namespace str_helpers
{
	inline vector<string> split(const string& str_to_split, char delimiter)
	{
		stringstream ss(str_to_split);
		string item;
		vector<string> parts;
		while (getline(ss, item, delimiter))
		{
			parts.push_back(item);
		}
		return parts;
	}

	inline bool is_equals_ignore_case(const string& a, const string& b)
	{
		return equal(a.begin(), a.end(), b.begin(), b.end(), [](char a, char b)
			{
				return tolower(a) == tolower(b);
			});
	}

	template <std::size_t size>
	string join(const string(&parts)[size], char delimiter)
	{
		stringstream ss;
		for (size_t i = 0; i < size; i++)
		{
			ss << parts[i];
			if ((i + 1) < size) {
				ss << delimiter;
			}
		}
		return ss.str();
	}

	inline string replace(std::string str, char old_value, char new_value)
	{
		std::replace(str.begin(), str.end(), old_value, new_value);
		return str;
	}
}
