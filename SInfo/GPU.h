#pragma once
#include <string>
#include <windows.h>
#include <iostream>
#include <array>
#include <vector>
#include <typeinfo>
#include "InitializesCOM.h"
#include "DataWork.h"

using namespace std;

class GPU {

public:

	struct ADAPTER {

		string videoCardName;

		string driverVersion;

		string driverDate;

		string adapterCompatibility;

		string videoProcessor;

		long long ramSize = 0;// max 4095mb,  AdapterRAM type = uint32, =)
	};


private:

	const string OBJECTPATH = "root\\cimv2";

	const string WQL = "SELECT * FROM ";

	template< typename T, size_t N >
	void receiving(array<T, N>& v, string _class_name);

	int adapterCount = 0;

	vector< ADAPTER > adapter_bufer;

	void setAdapterCount(int _adapterCount);

public:

	GPU(bool WMIRequest);

	string getGPUName_WinAPI();

	vector< ADAPTER > getADAPTERS();

	int getAdapteCount();
	
};