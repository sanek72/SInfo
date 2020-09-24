#pragma once

#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <typeinfo>
#include "InitializesCOM.h"
#include "DataWork.h"

using namespace std;

class Sound{

public:

	struct DEVICE {

		string manufacturer;
		string name;

	};

private:

	const string OBJECTPATH = "root\\cimv2";

	const string WQL = "SELECT * FROM ";

	template< typename T, size_t N >
	void receiving(array<T, N>& v, string _class_name);

	int deviceCount = 0;

	void setDeviceCount(int _deviceCount);

	vector< DEVICE > device_bufer;

public:

	Sound(bool WMIRequest);

	int getDeviceCount();

	vector< DEVICE > getDevice();

};


