#include "RAM.h"


RAM::RAM(){
    static const int physicalMemory_size = 36;
    static const std::string physicalMemory_class = "Win32_PhysicalMemory";
    std::array<std::string, physicalMemory_size> physicalMemory = { "Attributes", "BankLabel", "Capacity", "Caption", "ConfiguredClockSpeed", "ConfiguredVoltage", "CreationClassName",
        "DataWidth", "Description", "DeviceLocator", "FormFactor", "HotSwappable", "InstallDate", "InterleaveDataDepth", "InterleavePosition", "Manufacturer", "MaxVoltage",
        "MemoryType", "MinVoltage", "Model", "Name", "OtherIdentifyingInfo", "PartNumber", "PositionInRow", "PoweredOn", "Removable", "Replaceable", "SerialNumber", "SKU", "SMBIOSMemoryType",
        "Speed", "Status", "Tag","TotalWidth", "TypeDetail", "Version" };

    static const int physicalMemoryArray_size = 28;
    static const std::string physicalMemoryArray_class = "Win32_PhysicalMemoryArray";
    std::array<std::string, physicalMemoryArray_size> physicalMemoryArray = { "Caption", "CreationClassName", "Depth", "Description", "Height", "HotSwappable", "InstallDate",
        "Location", "Manufacturer", "MaxCapacity", "MaxCapacityEx", "MemoryDevices", "MemoryErrorCorrection", "Model", "Name", "OtherIdentifyingInfo", "PartNumber",
        "PoweredOn", "Removable", "Replaceable", "SerialNumber", "SKU", "Status", "Tag", "Use", "Version", "Weight", "Width" };

    static const int physicalMemoryLocation_size = 3;
    static const std::string physicalMemoryLocation_class = "Win32_PhysicalMemoryLocation";
    std::array<std::string, physicalMemoryLocation_size> physicalMemoryLocation = { "LocationWithinContainer", "PartComponent", "GroupComponent" };

        // true - будем собирать информацию для каждого модуля RAM
        //receiving(physicalMemory, physicalMemory_class, true);
        //receiving(physicalMemoryArray, physicalMemoryArray_class, false);
        //receiving(physicalMemoryLocation, physicalMemoryLocation_class, false);

}

template<typename T, std::size_t N>
void RAM::receiving(std::array<T, N>& v, std::string _class_name, bool m){

    size_t len = v.size();

    std::vector< std::string > properties;

    for (size_t i = 0; i < len; ++i) {
        properties.push_back(v[i]);
    }

    std::vector< std::string > value;

    if (InitializesCOM(ObjectPath, WQL + _class_name, properties).Initialize(value)) {
        
        //work
        if (m) {
            size_t all = value.size();

            for (size_t i = 0; i < all; i = i + len) {
                setModulesCount();
            }

            int a = 0, b = 0;

            MODUL m;

            size_t i = 0;

            do {
                
                if (b == len) {
                    m_buf.push_back(m);
                    b = 0;
                    a++;
                }
                
                if (i >= value.size()) {
                    break;
                }

                //std::cout << "Class[" + _class_name + "] propertie[" + properties[b] + "] modul(" + std::to_string(a) + ") =" + value[i] << std::endl;

                if (properties[b] == "Name") {

                    m.name = value[i];

                }

                if (properties[b] == "BankLabel") {

                    m.bank = value[i];

                }

                if (properties[b] == "Capacity") {

                    if (value[i] != "unavailable") {

                        m.ramSize = std::stoll(value[i]);

                    }
                    
                }

                if (properties[b] == "Speed") {

                    if (value[i] != "unavailable") {

                        m.speed = std::stoi(value[i]);
                    }

                }

                b++;
                i++;
            } while (i <= value.size());

        } else {

            for (size_t i = 0; i < value.size(); ++i) {
                
                //std::cout << "Clas[" + _class_name + "] propertie[" + properties[i] + "] = " + value[i]<< std::endl;

                ////

            }
        }

    }
    else {
        //erore 
        std::cout << typeid(RAM).name() << ". Error getting information." << std::endl;
    }

}


std::string RAM::getMemoryRAMsize_Win32() {
    ULONGLONG memKb;
    if (GetPhysicallyInstalledSystemMemory(&memKb)) {
        return std::to_string((memKb / 1024 / 1024));

    }else {

        printf(typeid(RAM).name(), ". Error getting information.");
        printf("%d\n", GetLastError());
        return "NULL";

    }

    return "NULL";

    //MEMORYSTATUSEX total_memory;
    //total_memory.dwLength = sizeof(total_memory);
    //GlobalMemoryStatusEx(&total_memory);

    //std::cout << "mb: " << (total_memory.ullTotalPhys / (1024 * 1024)) << std::endl;
    //std::cout << "gb: " << (total_memory.ullTotalPhys / (1024 * 1024) / 1000) << std::endl;
}

int RAM::getModulesCount(){
    return modulesCount;
}

std::vector<RAM::MODUL> RAM::getModulesRAM(){
    return m_buf;
}


void RAM::setModulesCount(){
    modulesCount++;
}
