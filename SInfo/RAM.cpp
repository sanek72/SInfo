#include "RAM.h"


RAM::RAM(bool WMIRequest) {

    if (WMIRequest) {
        static const int physicalMemory_size = 4;
        static const string physicalMemory_class = "Win32_PhysicalMemory";
        array<string, physicalMemory_size> physicalMemory = { "Name", "BankLabel", "Capacity", "Speed" };
        receiving(physicalMemory, physicalMemory_class);
    }

}

template< typename T, size_t N >
void RAM::receiving(array<T, N>& v, string _class_name) {
	size_t len = v.size();

	vector< string > properties;

	for (size_t i = 0; i < len; ++i) {
		properties.push_back(v[i]);
	}

	DataWork dataWork;

	InitializesCOM initCom;

	if (initCom.Initialize(OBJECTPATH, WQL + _class_name, properties, dataWork)) {

		//work
		setModulesCount(dataWork.data_count);

		for (int i = 1; i <= dataWork.data_count; ++i) {

			MODUL m;

			m.name = dataWork.getDataString("Name" + to_string(i));
			m.bank = dataWork.getDataString("BankLabel" + to_string(i));			
			m.ramSize = dataWork.uint64ToLongLong(dataWork.getDataString("Capacity" + std::to_string(i)));
			m.speed = dataWork.getDataLong("Speed" + std::to_string(i));

			modul_bufer.push_back(m);

		}

	} else {
		//erore
		cout << typeid(RAM).name() << ". Error getting information." << endl;
	}

}

long long RAM::getMemorySize_Win32() {

    long long s = 0;
    ULONGLONG memKb;
    if (GetPhysicallyInstalledSystemMemory(&memKb)) {
        s = memKb;

    } else {

        cout << typeid(RAM).name() << ". Error getting information. " << GetLastError() << endl;
        return s;

    }
    return s;

}

int RAM::getModulesCount(){
    return modulesCount;
}

vector<RAM::MODUL> RAM::getModulesRAM(){
    return modul_bufer;
}


void RAM::setModulesCount(int _modulesCount){
    modulesCount = _modulesCount;
}
