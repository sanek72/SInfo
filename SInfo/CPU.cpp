#include "CPU.h"

CPU::CPU(){

    static const int processor_size = 57;
    static const std::string processor_class = "Win32_Processor";
    std::array<std::string, processor_size> processor = { "AddressWidth", "Architecture", "AssetTag", "Availability", "Caption", "Characteristics", "ConfigManagerErrorCode",
        "ConfigManagerUserConfig", "CpuStatus", "CreationClassName", "CurrentClockSpeed", "CurrentVoltage", "DataWidth", "Description", "DeviceID", "ErrorCleared", "ErrorDescription", 
        "ExtClock", "Family", "InstallDate", "L2CacheSize", "L2CacheSpeed", "L3CacheSize", "L3CacheSpeed", "LastErrorCode", "Level", "LoadPercentage", "Manufacturer", "MaxClockSpeed", "Name", 
        "NumberOfCores", "NumberOfEnabledCore", "NumberOfLogicalProcessors","OtherFamilyDescription", "PartNumber", "PNPDeviceID", "PowerManagementCapabilities", "PowerManagementSupported", 
        "ProcessorId", "ProcessorType", "Revision", "Role", "SecondLevelAddressTranslationExtensions","SerialNumber", "SocketDesignation", "Status", "StatusInfo", "Stepping", 
        "SystemCreationClassName", "SystemName", "ThreadCount", "UniqueId", "UpgradeMethod", "Version", "VirtualizationFirmwareEnabled", "VMMonitorModeExtensions", "VoltageCaps"};

    if (!isInit) {

        receiving(processor, processor_class);
        CPU::isInit = true;

    }
}
//
template< typename T, std::size_t N >
void CPU::receiving(std::array<T, N>& v, std::string _class_name) {

    size_t len = v.size();

    std::vector< std::string > properties;

    for (size_t i = 0; i < len; ++i) {
        properties.push_back(v[i]);
    }


    InitializesCOM* initCOM;

    initCOM = new InitializesCOM(ObjectPath, WQL + _class_name, properties);

    std::vector< std::string > value;

    if (initCOM->Initialize(value)) {

        //work
        //setlocale(LC_CTYPE, "Russian");
        for (size_t i = 0; i < properties.size(); ++i) {

            //std::cout << "Class[" + _class_name + "] propertie[" + properties[i] + "] = " + value[i]<< std::endl;

            if (properties[i] == "Architecture") {

                setArchitecturer(value[i]);

            }

            if (properties[i] == "Name") {

                setProcessorName(value[i]);

            }

            if (properties[i] == "NumberOfCores") {

                setProcessorCores(value[i]);

            }
            if (properties[i] == "NumberOfLogicalProcessors") {

                setProcessorThreads(value[i]);

            }

            if (properties[i] == "SocketDesignation") {

                setSocket(value[i]);

            }

        }

    }
    else {
        //erore 
        std::cout << typeid(CPU).name() << ". Error getting information." << std::endl;
    }

    delete(initCOM);
}

std::string CPU::getProcessorName__cpuid(){

    int cpuidex;

    std::array<int, 4> cpui;
    std::vector<std::array<int, 4>> data;

    __cpuid(cpui.data(), 0x80000000);
    cpuidex = cpui[0];

    char cpu[0x40];
    memset(cpu, 0, sizeof(cpu));

    for (int i = 0x80000000; i <= cpuidex; ++i) {
        __cpuidex(cpui.data(), i, 0);
        data.push_back(cpui);

    }

    if (cpuidex >= 0x80000004) {

        memcpy(cpu, data[2].data(), sizeof(cpui));
        memcpy(cpu + 16, data[3].data(), sizeof(cpui));
        memcpy(cpu + 32, data[4].data(), sizeof(cpui));
    }

    return cpu;
}

int CPU::getProcessorCores_Win32() {
    //https://docs.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-system_logical_processor_information
    DWORD logicalProcessorCount = 0, i, len;
    DWORD dLen = 0x100 * sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
    PSYSTEM_LOGICAL_PROCESSOR_INFORMATION s = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)VirtualAlloc(NULL, dLen, MEM_COMMIT, PAGE_READWRITE);
    GetLogicalProcessorInformation(s, &dLen);
    if (s == NULL) {
        return 0;
    }
    len = dLen / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
    for (i = 0; i < len; i++) {
        if (s[i].Relationship == RelationProcessorCore) {
            logicalProcessorCount++;
        }
    }

    VirtualFree(s, dLen, 0);

    return logicalProcessorCount;

}

int CPU::getProcessorThreads_Win32() {

    SYSTEM_INFO s;
    GetSystemInfo(&s);

    return s.dwNumberOfProcessors;

}

std::string CPU::getArchitecture(){
    return architectureString(std::stoi(architecture));
}

void CPU::setArchitecturer(std::string _architecture){
    architecture = _architecture;
}

std::string CPU::getProcessorName(){
    return processorName;
}

void CPU::setProcessorName(std::string _processorName){
    processorName = _processorName;
}

int CPU::getProcessorCores(){
    return processorCores;
}

void CPU::setProcessorCores(std::string _processorCores){
    processorCores = std::stoi(_processorCores);
}

int CPU::getProcessorThreads(){
    return processorThreads;
}

void CPU::setProcessorThreads(std::string _processorThreads){
    processorThreads = std::stoi(_processorThreads);
}

std::string CPU::getSocket(){
    return socket;
}

void CPU::setSocket(std::string _socket){
    socket = _socket;
}

std::string CPU::architectureString(int a) {

    std::string s = "null";

    switch (a) {
    case 0:
        s = "x86";
        break;
    case 1:
        s = "MIPS";
        break;
    case 2:
        s = "Alpha ";
        break;
    case 3:
        s = "PowerPC  ";
        break;
    case 5:
        s = "ARM";
        break;
    case 6:
        s = "Intel Itanium-based";
        break;
    case 9:
        s = "x64 (AMD or Intel)";
        break;
    case 12:
        s = "ARM64";
        break;
    case 0xffff:
        s = "Unknown architecture.";
        break;
    }
    return s;
}


//Name
//NumberOfCores
//NumberOfLogicalProcessors
//SocketDesignation]