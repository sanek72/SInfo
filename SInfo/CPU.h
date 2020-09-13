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

	template< typename T, std::size_t N >
	void receiving(std::array<T, N>& v, std::string _class_name);

	std::string architecture;

	std::string processorName;

	std::string socket;

	int processorCores = 0;

	int processorThreads = 0;

	void setArchitecturer(std::string _architecture);

	void setProcessorName(std::string _processorName);

	void setProcessorCores(std::string _processorCores);

	void setProcessorThreads(std::string _processorThreads);

	void setSocket(std::string _socket);

public:

	CPU();

	std::string getProcessorName__cpuid();

	int getProcessorCores_Win32();

	int getProcessorThreads_Win32();

	std::string getArchitecture();

	std::string getProcessorName();

	int getProcessorCores();

	int getProcessorThreads();

	std::string getSocket();

	std::string architectureString(int a);

};