#pragma once
#include <string>
#include <windows.h>
#include <array>
#include <intrin.h>
#include <vector>
#include <iostream>
#include <typeinfo>
#include "InitializesCOM.h"


class CPU {

private:

	const std::string ObjectPath = "root\\cimv2";

	const std::string WQL = "SELECT * FROM ";

	bool isInit = false;

	template< typename T, std::size_t N >
	void receiving(std::array<T, N>& v, std::string _class_name);

	std::string architecture;

	std::string processorName;

	std::string socket;

	int processorCores;

	int processorThreads;



public:

	CPU();

	std::string getProcessorName__cpuid();

	int getProcessorCores_Win32();

	int getProcessorThreads_Win32();

	std::string getArchitecture();

	void setArchitecturer(std::string _architecture);

	std::string getProcessorName();

	void setProcessorName(std::string _processorName);

	int getProcessorCores();

	void setProcessorCores(std::string _processorCores);

	int getProcessorThreads();

	void setProcessorThreads(std::string _processorThreads);

	std::string getSocket();

	void setSocket(std::string _socket);

	std::string architectureString(int a);

};