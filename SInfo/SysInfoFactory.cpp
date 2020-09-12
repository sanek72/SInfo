#include "SysInfoFactory.h"


OS SysInfoFactory::getOSInformation(){
	return os;
}

CPU SysInfoFactory::getCPUInformation(){
	return cpu;
}

GPU SysInfoFactory::getGPUInformation(){
	return gpu;
}

Motherboard SysInfoFactory::getMotherboardInformation(){
	return board;
}

RAM SysInfoFactory::getRAMInformation(){
	return ram;
}

BIOS SysInfoFactory::getBIOSInformation(){
	return bios;
}
