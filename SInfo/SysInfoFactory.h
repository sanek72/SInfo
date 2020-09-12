#pragma once

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "Secur32.lib")

#include "Motherboard.h"
#include "OS.h"
#include <string>
#include "CPU.h"
#include "GPU.h"
#include "RAM.h"



class SysInfoFactory {

private:

	Motherboard board;
	OS os;
	CPU cpu;
	GPU gpu;
	RAM ram;

public:

	OS getOSInformation();

	CPU getCPUInformation();

	GPU getGPUInformation();

	Motherboard getMotherboardInformation();

	RAM getRAMInformation();

};

