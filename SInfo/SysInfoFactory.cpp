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

	cout << "\t" << "Video adapters:" << endl;
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
	cout << "\t" << "Total memory: " << ram.getMemorySize_WinAPI() / 1024 / 1024 << "gb" << endl;
	cout << "\n";

	BIOS bios = BIOS(true);

	cout << "\t" << "BIOS:" << endl;
	cout << "\t" << bios.getManufacturer() << endl;
	cout << "\t" << bios.getName() << endl;
	cout << "\t" << bios.getVersion() << endl;
	cout << "\t" << "Serial Number - " + bios.getSerialNumber() << endl;

	cout << "\n";

	DISKS disks = DISKS(true);

	cout << "\t" << "Physical disk:" << endl;
	for (DISKS::PHYSICALDISK pd : disks.getFDisks()) {
		cout << "\t" << pd.name << endl;
		cout << "\t" << pd.model  << endl;
		cout << "\t" << "Size - " <<  pd.size / 1024 / 1024 / 1024 << "gb  " << endl;
		cout << "\t" << "Serial Number - " << pd.serialNumber << endl;
		cout << "\t" << "Interface Type - " << pd.interfaceType << endl;
		cout << "\n";
	}

	cout << "\t" << "Logical disk:" << endl;
	for (DISKS::LOGICALDISK ld : disks.getLDisks()) {
		cout << "\t" << ld.name << endl;
		cout << "\t" << disks.getDiskTypeString(ld.type) << endl;
		cout << "\t" << "File system - " << ld.fileSystem << endl;
		cout << "\t" << "Size - " << ld.size / 1024 / 1024 / 1024 << "gb  " << endl;
		cout << "\t" << "Free space - " << ld.free_size / 1024 / 1024 / 1024 << "gb  " << endl;
		cout << "\n";
	}

	//example winApi
	//cout << "\t" << "Logical disk:" << endl;
	//for (string d : disks.getLogicaDisk()) {
	//	cout << "\t" << d  << endl;
	//    cout << "\t" << disks.getLogicaDiskType(d) << endl;
	//	cout << "\t" << "File system - " << disks.getLogicaDiskFaileSystem(d) << endl;
	//	cout << "\t" << "Total size - " << disks.getLogicaDiskTotalSize(d) / 1024 / 1024 / 1024 << "gb  " << endl;
	//	cout << "\t" << "Free size - " << disks.getLogicaDiskFreeSize(d) / 1024 / 1024 / 1024 << "gb  " << endl;
	//	cout << "\n";
	//}

	Sound s = Sound(true);

	cout << "\t" << "Sound device:" << endl;
	for (Sound::DEVICE sd : s.getDevice()) {
		cout << "\t" << sd.manufacturer << "  |  "  << sd.name << endl;
		
	}
	cout << "\n";

	Network net = Network(true);

	cout << "\t" << "Network adapters:" << endl;
	for (Network::ADAPTER n : net.getAdapters()) {
		cout << "\t" << n.manufacturer << endl;
		cout << "\t" << n.name << endl;
		cout << "\t" << "MAC Address - " << n.MACAddress << endl;
		cout << "\t" << "Adapter enabled - " << (n.netEnabled ? "true" : "false") << endl;
		cout << "\n";
	}
	cout << "\n";

}


