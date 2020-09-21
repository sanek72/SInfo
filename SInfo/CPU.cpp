#include "CPU.h"

CPU::CPU(bool WMIRequest) {

    if (WMIRequest) {
        static const int PROCESSOR_SIZE = 57;
        static const std::string PROCESSOR_CLASS = "Win32_Processor";
        std::array<std::string, PROCESSOR_SIZE> processor = { "Architecture", "Name", "NumberOfCores", "NumberOfLogicalProcessors", "SocketDesignation" };
        receiving(processor, PROCESSOR_CLASS);
    }

}

template< typename T, size_t N >
void CPU::receiving(array<T, N>& v, string _class_name) {

    size_t len = v.size();

    vector< string > properties;

    for (size_t i = 0; i < len; ++i) {
        properties.push_back(v[i]);
    }

    DataWork dataWork;

    InitializesCOM initCom;

    if (initCom.Initialize(OBJECTPATH, WQL + _class_name, properties, dataWork)) {

        //work
        for (int i = 1; i <= dataWork.data_count; ++i) {

            setProcessorName(dataWork.getDataString("Name" + to_string(i)));
            setArchitecturer(dataWork.getDataLong("Architecture" + to_string(i)));
            setProcessorCores(dataWork.getDataLong("NumberOfCores" + to_string(i)));
            setProcessorThreads(dataWork.getDataLong("NumberOfLogicalProcessors" + to_string(i)));
            setSocket(dataWork.getDataString("SocketDesignation" + to_string(i)));

        }

    } else {
        //erore
        cout << typeid(CPU).name() << ". Error getting information." << endl;
    }

}


string CPU::getProcessorName__cpuid() {

    int cpuidex;

    array<int, 4> cpui;
    vector<array<int, 4>> data;

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


string CPU::getArchitecture(){
    return architectureString(architecture);
}

void CPU::setArchitecturer(long _architecture){
    if (_architecture != -1) {
        architecture = _architecture;
    }  
}

string CPU::getProcessorName(){
    return processorName;
}

void CPU::setProcessorName(string _processorName){
    processorName = _processorName;
}

int CPU::getProcessorCores(){
    return processorCores;
}

void CPU::setProcessorCores(int _processorCores){
    processorCores = _processorCores;
}

int CPU::getProcessorThreads(){
    return processorThreads;
}

void CPU::setProcessorThreads(int _processorThreads){
    processorThreads = _processorThreads;
}

string CPU::getSocket(){
    return socket;
}

void CPU::setSocket(string _socket){
    socket = _socket;
}

string CPU::architectureString(int a) {

    string s = "unavailable";

    switch (a) {
    case 0:
        s = "x86";
        break;
    case 1:
        s = "MIPS";
        break;
    case 2:
        s = "Alpha";
        break;
    case 3:
        s = "PowerPC ";
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
        s = "unavailable";
        break;
    }
    return s;
}
