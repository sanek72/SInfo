#pragma once

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Secur32.lib")

#include <windows.h>
#define SECURITY_WIN32
#include <Security.h>
#include <secext.h>
#include <iostream>
#include <typeinfo>
#include "InitializesCOM.h"
#include <array>
#include "DataWork.h"

using namespace std;

class OS{

private:

	const string OBJECTPATH = "root\\cimv2";

	const string WQL = "SELECT * FROM ";

	string OSName;

	string сomputerName;

	string buildNumber;

	string OSArchitecture;

	string localDateTime;

	string registeredUser;

	template< typename T, size_t N >
	void receiving(array<T, N>& v, string _class_name);

	void setOSName(string _OSName);

	void setComputerName(string _сomputerName);

	void setBuildNumber(string _buildNumber);

	void setOSArchitecture(string _OSArchitecture);

	void setLocalDateTime(string _localDateTime);

	void setRegisteredUser(string _registeredUser);

public:

	OS(bool WMIRequest);

	string getComputerName_Win32();

	string getOSName_Win32();

	string getOSName();

	string getComputerName();

	string getBuildNumber();

	string getOSArchitecture();

	string getLocalDateTime();

	string getRegisteredUser();

	string getUserNameEx();

	string getUserName();
};

