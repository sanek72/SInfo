#pragma once

#include <Wbemidl.h>
#include <comdef.h>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include "DataWork.h"


#pragma comment( lib, "Wbemuuid.lib" )

using namespace std;

class InitializesCOM{

private:

	static const  int VBSTRING_TYPE = 8;
	static const  int VBARRAY_TYPE = 8192;
	static const  int VBBOOLEAN_TYPE = 11;
	static const  int VBINTEGER_TYPE = 2;
	static const  int VBBYTE_TYPE = 17;
	static const  int VBLONG_TYPE = 3;
	static const  int VTNULL_TYPE = 1;

public:

	bool Initialize(string objectPath, string wql, vector< string > _properties, DataWork &_dataWork);

};

