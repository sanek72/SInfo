#pragma once

#include <windows.h>
#define SECURITY_WIN32
#include <Security.h>
#include <secext.h>


#include <iostream>
#include <typeinfo>
#include "InitializesCOM.h"
#include <array>


class OS{

private:

	const std::string ObjectPath = "root\\cimv2";

	const std::string WQL = "SELECT * FROM ";

	bool isInit = false;

	std::string OSName;

	std::string сomputerName;

	std::string buildNumber;

	int freePhysicalMemory = 0;

	std::string OSArchitecture;

	std::string localDateTime;

	std::string registeredUser;

	template< typename T, std::size_t N >
	void receiving(std::array<T, N>& v, std::string _class_name);

public:

	OS();

	std::string getComputerName_Win32();

	std::string getOSName_Win32();

	std::string getOSName();

	void setOSName(std::string _OSName);

	std::string getComputerName();

	void setComputerName(std::string _сomputerName);

	std::string getBuildNumber();

	void setBuildNumber(std::string _buildNumber);

	//int getFreePhysicalMemory();

	//void setFreePhysicalMemory(std::string _freePhysicalMemory);

	std::string getOSArchitecture();

	void setOSArchitecture(std::string _OSArchitecture);

	std::string getLocalDateTime();

	void setLocalDateTime(std::string _localDateTime);

	std::string getRegisteredUser();

	void setRegisteredUser(std::string _registeredUser);

	std::string getUserNameEx();

	std::string getUserName();
};

