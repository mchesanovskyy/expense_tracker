#pragma once
#include <iostream>

namespace CoutHelper
{
	inline void WriteHeader(string name, int lineLen = 48)
	{
		int availableNameSpace = (lineLen - 2 - name.length());
		int padLeft = availableNameSpace / 2;
		int padRight = availableNameSpace - padLeft;
		cout << std::string(lineLen, '-') << endl;
		cout << "|";
		cout << std::string(padLeft, ' ') << name;
		cout << std::string(padRight, ' ') << "|" << endl;
		cout << std::string(lineLen, '-') << endl;
	}

	inline void WriteParameter(string name, string value, const int nameLen)
	{
		cout << setw(nameLen) << left << name << ": " << value << endl;
	}

	inline void WriteParameter(string name, int value, const int nameLen)
	{
		WriteParameter(name, to_string(value), nameLen);
	}

	inline void WriteParameter(string name, double value, const int nameLen)
	{
		WriteParameter(name, to_string(value), nameLen);
	}

	inline void WriteParameter(string name, time_t value, const int nameLen)
	{
		WriteParameter(name, to_string(value), nameLen);
	}
};

