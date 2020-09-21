#pragma once
#include <string>
#include <array>
#include <vector>
#include "InitializesCOM.h"
#include <windows.h>
#include <typeinfo>
#include "DataWork.h"

using namespace std;

class RAM{

public:

	struct MODUL {

		string name;
		string bank;
		long long ramSize = 0;
		long speed = 0;

	};

private:

	const string OBJECTPATH = "root\\cimv2";

	const string WQL = "SELECT * FROM ";

	template< typename T, size_t N >
	void receiving(array<T, N>& v, string _class_name);

	int modulesCount = 0;

	void setModulesCount(int _modulesCount);

	vector< MODUL > modul_bufer;

public:

	RAM(bool WMIRequest);

	long long getMemorySize_Win32();

	int getModulesCount();

	vector< MODUL > getModulesRAM();	

};


