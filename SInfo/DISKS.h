#pragma once

#include <string>
#include <array>
#include <vector>
#include "InitializesCOM.h"
#include <windows.h>
#include <typeinfo>
#include "DataWork.h"
#include "Utils.h"


using namespace std;

class DISKS{

public:

	struct PHYSICALDISK {

		string model;
		string name;
		long long size = 0;
		string serialNumber;
		string interfaceType;

	};

	struct LOGICALDISK {

		string name;
		long long size = 0;
		long long free_size = 0;
		string fileSystem;
		long type;

	};

private:

    const string DISKDRIVE_CLASS = "Win32_DiskDrive";

    const string LOGICALDISK_CLASS = "Win32_LogicalDisk";

	const string OBJECTPATH = "root\\cimv2";

	const string WQL = "SELECT * FROM ";

	template< typename T, size_t N >
	void receiving(array<T, N>& v, string _class_name);

	vector< PHYSICALDISK > fdisk_bufer;

	vector< LOGICALDISK > ldisk_bufer;

	int fhysicalDiskCount = 0;

	int logicalDiskCount = 0;

	void setFhysicalDiskCount(int _fhysicalDiskCount);

	void setLogicalDiskCount(int _logicalDiskCount);

public:

	DISKS(bool WMIRequest);

	int getFhysicalDiskCount();

	int getLogicalDiskCount();

	vector< PHYSICALDISK > getFDisks();

	vector< LOGICALDISK > getLDisks();

	vector< string > getLogicaDisk();

	long long getLogicaDiskTotalSize(string drive);

	long long getLogicaDiskFreeSize(string drive);

	string getLogicaDiskType(string _drive);

	string getLogicaDiskFaileSystem(string _drive);

	string getDiskTypeString(int _type);

};
