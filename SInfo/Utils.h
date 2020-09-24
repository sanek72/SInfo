#pragma once

#include <locale>
#include <codecvt>
#include <string>
#include <iostream>

using namespace std;

class Utils {

public:

	static string getCIM_DATETIME(string value);

	static wstring s2ws(const string& str);

	static string ws2s(const wstring& wstr);

};