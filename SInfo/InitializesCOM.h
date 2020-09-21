#pragma once

#include <Wbemidl.h>
#include <comdef.h>
#include <cstring>
#include <iostream>
#include <string>
#include <comutil.h>//del
#include <vector>
#include "DataWork.h"


#pragma comment( lib, "Wbemuuid.lib" )


class InitializesCOM{

private:

	static const  int VBSTRING_TYPE = 8;
	static const  int VBARRAY_TYPE = 8192;
	static const  int VBBOOLEAN_TYPE = 11;
	static const  int VBINTEGER_TYPE = 2;
	static const  int VBBYTE_TYPE = 17;
	static const  int VBLONG_TYPE = 3;
	static const  int VTNULL_TYPE = 1;

	struct connect  {//del
		std::string objectPath;
		std::string wql;
		std::vector< std::string > properties;
	};

	connect c;

	std::string getArrayValues_(HRESULT hr, SAFEARRAY* parray, int vType);	

public:

	InitializesCOM();

	InitializesCOM(std::string objectPath, std::string wql, std::vector< std::string > _properties);

	bool Initialize(std::vector< std::string > &_value);

	bool Initialize(std::string objectPath, std::string wql, std::vector< std::string > _properties, DataWork &_dataWork);

};

