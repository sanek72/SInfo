#pragma once

#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <typeinfo>
#include "InitializesCOM.h"
#include "DataWork.h"

using namespace std;

class BIOS{

private:

	string OBJECTPATH = "root\\cimv2";

	string WQL = "SELECT * FROM ";

	template< typename T, size_t N >
	void receiving(array<T, N>& v, string _class_name);

	void setManufacturer(string _manufacturer);

	void setName(string _name);

	void setVersion(string _version);

	void setSerialNumber(string _serialNumber);

	string manufacturer;

	string name;

	string version;

	string serialNumber;


public:

	BIOS(bool WMIRequest);

	string getManufacturer();

	string getName();

	string getVersion();

	string getSerialNumber();

};

