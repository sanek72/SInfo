#pragma once
#include <string>
#include <windows.h>
#include <array>
#include <intrin.h>
#include <vector>
#include <iostream>
#include <typeinfo>
#include "InitializesCOM.h"
#include "DataWork.h"

using namespace std;

class CPU {

private:

	const string OBJECTPATH = "root\\cimv2";

	const string WQL = "SELECT * FROM ";

	template< typename T, size_t N >
	void receiving(array<T, N>& v, string _class_name);

	long architecture = 0xffff;

	string processorName;

	string socket;

	int processorCores = 0;

	int processorThreads = 0;

	void setArchitecturer(long _architecture);

	void setProcessorName(string _processorName);

	void setProcessorCores(int _processorCores);

	void setProcessorThreads(int _processorThreads);

	void setSocket(string _socket);

public:

	CPU(bool WMIRequest);

	string getProcessorName__cpuid();

	int getProcessorCores_WinAPI();

	int getProcessorThreads_WinAPI();

	string getArchitecture();

	string getProcessorName();

	int getProcessorCores();

	int getProcessorThreads();

	string getSocket();

	string architectureString(int a);

};