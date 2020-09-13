#pragma once
#include <string>
#include <array>
#include <vector>
#include "InitializesCOM.h"
#include <windows.h>
#include <typeinfo>

class RAM{

	const std::string ObjectPath = "root\\cimv2";

	const std::string WQL = "SELECT * FROM ";

	template< typename T, std::size_t N >
	void receiving(std::array<T, N>& v, std::string _class_name, bool m);

	int modulesCount = 0;

	struct MODUL{

		std::string name;
		std::string bank;
		long long ramSize = 0;
		int speed = 0;

	};


	void setModulesCount();

	std::vector< MODUL > m_buf;

public:

	RAM();

	std::string getMemoryRAMsize_Win32();

	int getModulesCount();

	std::vector< MODUL > getModulesRAM();	

};


