#include "Utils.h"

//https://docs.microsoft.com/en-us/windows/win32/wmisdk/cim-datetime
string Utils::getCIM_DATETIME(string value) {

	string s = "";

	if (value.size() != 25) {
		return "data wrong";
	}

	s += value.substr(0, 4);
	s += "/";
	s += value.substr(4, 2);
	s += "/";
	s += value.substr(6, 2);
	s += " ";
	s += value.substr(8, 2);
	s += ":";
	s += value.substr(10, 2);
	s += ":";
	s += value.substr(12, 2);

	return s;
}
