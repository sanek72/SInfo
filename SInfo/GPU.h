#pragma once
#include <string>
#include <windows.h>
#include <iostream>
#include <sstream>
#include <array>
#include <vector>
#include <typeinfo>
#include "InitializesCOM.h"

class GPU {

private:

	const std::string ObjectPath = "root\\cimv2";

	const std::string WQL = "SELECT * FROM ";

	template< typename T, std::size_t N >
	void receiving(std::array<T, N>& v, std::string _class_name);

	//void setVideoCardName(std::string _videoCardName);

	//void setDriverVersion(std::string _driverVersion);

	//void setDriverDate(std::string _driverDate);

	//void setAdapterCompatibility(std::string _adapterCompatibility);

	//void setVideoProcessor(std::string _videoProcessor);

	//void setInstalledDisplayDrivers(std::string _displayDrivers);

	//long long ramSize = 0;

	//void setRamSize(std::string _ramSize);

	int adapter_count = 0;

	void setAdapterCount();

	struct ADAPTER {

		std::string videoCardName;

		std::string driverVersion;

		std::string driverDate;

		std::string adapterCompatibility;

		std::string videoProcessor;

		std::vector< std::string > installedDisplayDrivers;

		long long ramSize = 0;
	};

	std::vector< ADAPTER > a_buf;

public:

	GPU();

	std::string getGPUName_Win32();

	//std::string getVideoCardName();

	//std::string getDriverVersion();

	//std::string getDriverDate();

	//std::string getAdapterCompatibility();

	//std::string getVideoProcessor();

	//std::vector< std::string > getInstalledDisplayDrivers();

	//long long getRamSize();

	int getAdapterCount();

	std::vector< ADAPTER > getADAPTERS();
	
};