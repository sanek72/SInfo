#pragma once

#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <typeinfo>
#include "InitializesCOM.h"

class BIOS{

	std::string manufacturer;

	std::string name;

	std::string version;

	std::string serialNumber;

private:

	const std::string ObjectPath = "root\\cimv2";

	const std::string WQL = "SELECT * FROM ";

	bool isInit = false;

	template< typename T, std::size_t N >
	void receiving(std::array<T, N>& v, std::string _class_name);

	void setManufacturer(std::string _manufacturer);

	void setName(std::string _name);

	void setVersion(std::string _version);

	void setSerialNumber(std::string _serialNumber);

public:

	std::string getManufacturer();

	std::string getName();

	std::string getVersion();

	std::string getSerialNumber();

	BIOS();

};

