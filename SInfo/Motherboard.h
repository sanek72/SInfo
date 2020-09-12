#pragma once
#include <iostream>
#include "InitializesCOM.h"
#include <typeinfo>
#include <array>

class Motherboard{

private:

	const std::string ObjectPath = "root\\cimv2";

	const std::string WQL = "SELECT * FROM ";

	bool isInit = false;

	std::string manufacturer;

	std::string product;

	std::string serialNumber;

	template< typename T, std::size_t N >
	void receiving(std::array<T, N>& v, std::string _class_name);

	void setManufacturer(std::string _manufacturer);

	void setProduct(std::string _product);

	void setSerialNumber(std::string _serialNumber);

public:

	Motherboard ();

    std::string getManufacturer();

	std::string getProduct();

	std::string getSerialNumber();

};

