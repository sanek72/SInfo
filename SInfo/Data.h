#pragma once
#include <Wbemidl.h>
#include <comdef.h>
#include <map>
#include <string>

class Data{

public:

	int data_count = 0;

	std::map < std::string, BSTR> bstr;
	std::map < std::string, std::string> array_string;
	std::map < std::string, UINT> array_uint;
	std::map < std::string, VARIANT_BOOL> boolean;
	std::map < std::string, INT> integer;
	std::map < std::string, UINT> uint;

};

