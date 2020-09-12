#include <iostream>
#include <cstdlib> 
#include "SysInfoFactory.h"
#include <locale.h> 
#include "Utils.h"

using namespace std;
SysInfoFactory info;
Utils util;

int main(){
    //
    setlocale(LC_CTYPE, "Russian");

    cout << "  Hello " + info.getOSInformation().getUserName() << endl;
    ////cout << "\n" << endl;

    cout << "____________________________________________________\n" << endl;
    cout <<  "  Date : " + util.getCIM_DATETIME(info.getOSInformation().getLocalDateTime()) + "\n" +
        "  Computer Name: " + info.getOSInformation().getComputerName() + "\n" +
        "  OS: " + info.getOSInformation().getOSName() + " " + info.getOSInformation().getOSArchitecture() + "\n" +
        "  BuildNumber: " + info.getOSInformation().getBuildNumber() + "\n" +
        "  RegisteredUser: " + info.getOSInformation().getRegisteredUser()  << endl;

    cout << "____________________________________________________\n" << endl;
    cout << "  Processor: " + info.getCPUInformation().getProcessorName() << endl;
    cout << "   (Core: " + std::to_string(info.getCPUInformation().getProcessorCores()) +
        ", Threads: " + std::to_string(info.getCPUInformation().getProcessorThreads()) + ")" << endl;
    cout << "  Architecture: " + info.getCPUInformation().getArchitecture() << endl;
    cout << "  Socket: " + info.getCPUInformation().getSocket() << endl;

    cout << "____________________________________________________\n" << endl;

    cout << "  Video card: " + info.getGPUInformation().getGPUName_Win32() << endl;

    cout << "____________________________________________________\n" << endl;
    cout << "  Motherboard:" << endl;
    cout << "  " + info.getMotherboardInformation().getManufacturer() + "\n" +
        "  " + info.getMotherboardInformation().getProduct() + "\n" +
        "  Serial Number - " + info.getMotherboardInformation().getSerialNumber()  << endl;

    cout << "____________________________________________________\n" << endl;

    cout << "  Memory RAM modules count: " + std::to_string(info.getRAMInformation().getModulesCount())  << endl;
    for (int i = 0; i < info.getRAMInformation().getModulesCount(); ++i) {
        cout << "  Modul(" + std::to_string(i) + "): " + info.getRAMInformation().getModulesRAM()[i].name +
            "  " + info.getRAMInformation().getModulesRAM()[i].bank  +
            "  " + std::to_string(info.getRAMInformation().getModulesRAM()[i].ramSize/1024/1024/1024) + "gb" +
            "  " + std::to_string(info.getRAMInformation().getModulesRAM()[i].speed) + "MHz" << endl;
    }
    cout << "  Memory RAM size: " + info.getRAMInformation().getMemoryRAMsize_Win32() + "gb" << endl;
    cout << "____________________________________________________\n\n" << endl;

    ////cout << "\n" << endl;


    system("pause"); 
    return 0;
}

