#include "SysInfoFactory.h"

SysInfoFactory::SysInfoFactory(){
	gathered();
}

void SysInfoFactory::gathered(){

	Utils util;

	cout << "\n";

	OS os = OS(true);

	cout << "\t" << "Hello " << os.getUserName() << endl;
	cout << "\n";
	cout << "\t" << "Computer Name: " << os.getComputerName() << endl;
	cout << "\t" << "OS: " << os.getOSName() << " " << os.getOSArchitecture() << endl;
	cout << "\t" << "BuildNumber: " << os.getBuildNumber() << endl;
	cout << "\n";

	CPU cpu = CPU(true);

	cout << "\t" << "Processor:" << endl;
	cout << "\t" << cpu.getProcessorName() << " (Core: " << cpu.getProcessorCores() << ", Threads: " << cpu.getProcessorThreads() << ")" << endl;
	cout << "\t" << "Architecture: " + cpu.getArchitecture() << endl;
	cout << "\t" << "Socket: " + cpu.getSocket() << endl;
	cout << "\n";

	GPU gpu = GPU(true);

	cout << "\t" << "Video adapter:" << endl;
	for (GPU::ADAPTER a : gpu.getADAPTERS()) {
		cout << "\t" << a.adapterCompatibility << endl;
		cout << "\t" << a.videoCardName << endl;
		cout << "\t" << "Draiver vesion: " << a.driverVersion << " Date: " << util.getCIM_DATETIME(a.driverDate) << endl;
		cout << "\t" << "Memory size " << a.ramSize / 1024 / 1024 << "mb" << endl; 
		cout << "\t" << "VideoProcessor: " << a.videoProcessor << endl;
	}
	cout << "\n";

	Motherboard motherboard = Motherboard(true);

	cout << "\t" << "Motherboard:" << endl;
	cout << "\t" << motherboard.getManufacturer() << endl;
	cout << "\t" << motherboard.getProduct() << endl;
	cout << "\t" << "Serial Number - " << motherboard.getSerialNumber()  << endl;
	cout << "\n";

	RAM ram = RAM(true);

	cout << "\t" << "Memory RAM modules count: " << ram.getModulesCount() << endl;
	for (RAM::MODUL m : ram.getModulesRAM()) {
		cout << "\t" << m.name << "  " << m.bank << "  " << m.ramSize / 1024 / 1024 / 1024 << "gb  " << m.speed << "MHz" << endl;
	}
	cout << "\t" << "Total memory: " << ram.getMemorySize_Win32() / 1024 / 1024 << "gb" << endl;
	cout << "\n";

	BIOS bios = BIOS(true);

	cout << "\t" << "BIOS:" << endl;
	cout << "\t" << bios.getManufacturer() << endl;
	cout << "\t" << bios.getName() << endl;
	cout << "\t" << bios.getVersion() << endl;
	cout << "\t" << "Serial Number - " + bios.getSerialNumber() << endl;

	cout << "\n";

}


