#pragma once
#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <typeinfo>
#include "InitializesCOM.h"
#include "DataWork.h"

using namespace std;

class Network{

public:

	struct ADAPTER {

		string manufacturer;
		string name;
		string MACAddress;
		bool netEnabled = false;

	};

private:

	const string OBJECTPATH = "root\\cimv2";

	const string WQL = "SELECT * FROM ";

	const string FILTER_WQL = " WHERE PhysicalAdapter=TRUE";

	template< typename T, size_t N >
	void receiving(array<T, N>& v, string _class_name);

	int adapterCount = 0;

	void setAdapterCount(int _adapterCount);

	vector< ADAPTER > adapter_bufer;

public:

	Network(bool WMIRequest);

	int getAdapterCount();

	vector< ADAPTER > getAdapters();

};


