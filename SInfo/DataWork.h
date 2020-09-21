#pragma once
#include <string>
#include <Wbemidl.h>
#include <comutil.h>
#include <iostream>
#include <map>

using namespace std;

class DataWork{

private:

	struct DATA {

		map < string, string> bstr;
		map < string, VARIANT_BOOL> boolean;
		map < string, INT> integer;
		map < string, UINT> longer;

	};

	DATA data;

public:

	int data_count = 0;

	void setDataBSTR(string _key, BSTR _bstr);

	void setDataLong(string _key, UINT _uint);

	string getDataString(string _key);

	long long getDataLongLong(string _key);

	long getDataLong(string _key);

	long long uint64ToLongLong(string _value);

	BSTR convertStringToBSTR(string _value);
};

