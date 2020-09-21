#pragma once
#include <string>
#include <Wbemidl.h>
#include <comutil.h>
#include <iostream>
#include <map>

class DataWork{

private:

	struct DATA {

		std::map < std::string, std::string> bstr;
		std::map < std::string, VARIANT_BOOL> boolean;
		std::map < std::string, INT> integer;
		std::map < std::string, UINT> longer;

	};

	DATA data;

public:

	int data_count = 0;

	void setDataBSTR(std::string _key, BSTR _bstr);

	void setDataLong(std::string _key, UINT _uint);

	std::string getDataString(std::string _key);

	long long getDataLong(std::string _key);

	BSTR convertStringToBSTR(std::string _value);
};

