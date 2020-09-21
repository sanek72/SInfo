#pragma once
#include <iostream>
#include "InitializesCOM.h"
#include <typeinfo>
#include <array>
#include "DataWork.h"

using namespace std;

class Motherboard{

private:

	const string OBJECTPATH = "root\\cimv2";

	const string WQL = "SELECT * FROM ";

	string manufacturer;

	string product;

	string serialNumber;

	template< typename T, size_t N >
	void receiving(array<T, N>& v, string _class_name);

	void setManufacturer(string _manufacturer);

	void setProduct(string _product);

	void setSerialNumber(string _serialNumber);

public:

	Motherboard (bool WMIRequest);

    string getManufacturer();

	string getProduct();

	string getSerialNumber();

};

