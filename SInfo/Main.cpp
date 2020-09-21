#include <iostream>
#include <cstdlib> 
#include "SysInfoFactory.h"
#include <locale.h> 
#include "Utils.h"

using namespace std;


int main(){

    setlocale(LC_CTYPE, "Russian");

    SysInfoFactory info;

    //Utils util;

    //cout << "  Hello " + info.getOSInformation().getUserName() << endl;

    //cout << "____________________________________________________\n" << endl;
    //cout <</*  "  Date : " + util.getCIM_DATETIME(info.getOSInformation().getLocalDateTime()) + "\n" +*/
    //    "  Computer Name: " + info.getOSInformation().getComputerName() + "\n" +
    //    "  OS: " + info.getOSInformation().getOSName() + " " + info.getOSInformation().getOSArchitecture() + "\n" +
    //    "  BuildNumber: " + info.getOSInformation().getBuildNumber() + "\n" +
    //    "  RegisteredUser: " + info.getOSInformation().getRegisteredUser()  << endl;

    //cout << "____________________________________________________\n" << endl;
    //cout << "  Processor: "  << endl;
    //cout << "  " + info.getCPUInformation().getProcessorName() << endl;
    //cout << "   (Core: " + std::to_string(info.getCPUInformation().getProcessorCores()) +
    //    ", Threads: " + std::to_string(info.getCPUInformation().getProcessorThreads()) + ")" << endl;
    //cout << "  Architecture: " + info.getCPUInformation().getArchitecture() << endl;
    //cout << "  Socket: " + info.getCPUInformation().getSocket() << endl;

    //cout << "____________________________________________________\n" << endl;

    //cout << "  Video adapter: " << endl;
    //if (info.getGPUInformation().getAdapterCount() == 1) {

    //    cout << "  " + info.getGPUInformation().getADAPTERS()[0].adapterCompatibility << endl;
    //    cout << "  " + info.getGPUInformation().getADAPTERS()[0].videoCardName << endl;
    //    cout << "  Draiver vesion: " + info.getGPUInformation().getADAPTERS()[0].driverVersion + " Date: " + util.getCIM_DATETIME(info.getGPUInformation().getADAPTERS()[0].driverDate) << endl;
    //    for (std::string s : info.getGPUInformation().getADAPTERS()[0].installedDisplayDrivers) {
    //        cout << "  " + s << endl;
    //    }
    //cout << "  Memory size " + std::to_string(info.getGPUInformation().getADAPTERS()[0].ramSize / 1024 / 1024) + "mb" << endl; // max 4095mb,  AdapterRAM type = uint32, =)
    //cout << "  VideoProcessor: " + info.getGPUInformation().getADAPTERS()[0].videoProcessor << endl;

    //} else {
    //    for (int i = 0; i < info.getGPUInformation().getAdapterCount(); ++i) {
    //        cout << endl;
    //        cout << "  Adapter(" + std::to_string(i+1) + "):" << endl;
    //        cout << "  " + info.getGPUInformation().getADAPTERS()[i].adapterCompatibility << endl;
    //        cout << "  " + info.getGPUInformation().getADAPTERS()[i].videoCardName << endl;
    //        cout << "  Draiver vesion: " + info.getGPUInformation().getADAPTERS()[i].driverVersion + " Date: " + util.getCIM_DATETIME(info.getGPUInformation().getADAPTERS()[i].driverDate) << endl;
    //        for (std::string s : info.getGPUInformation().getADAPTERS()[i].installedDisplayDrivers) {
    //            cout << "  " + s << endl;
    //        }
    //        cout << "  Memory size " + std::to_string(info.getGPUInformation().getADAPTERS()[i].ramSize / 1024 / 1024) + "mb" << endl; // max 4095mb,  AdapterRAM type = uint32, =)
    //        cout << "  VideoProcessor: " + info.getGPUInformation().getADAPTERS()[i].videoProcessor << endl;
    //        cout << endl;
    //    }
    //}

    //cout << "____________________________________________________\n" << endl;

    //cout << "  Motherboard:" << endl;
    //cout << "  " + info.getMotherboardInformation().getManufacturer() + "\n" +
    //    "  " + info.getMotherboardInformation().getProduct() + "\n" +
    //    "  Serial Number - " + info.getMotherboardInformation().getSerialNumber()  << endl;

    //cout << "____________________________________________________\n" << endl;

    //cout << "  Memory RAM modules count: " + std::to_string(info.getRAMInformation().getModulesCount())  << endl;
    //for (int i = 0; i < info.getRAMInformation().getModulesCount(); ++i) {

    //    cout << "  Modul(" + std::to_string(i+1) + "): " + info.getRAMInformation().getModulesRAM()[i].name +
    //        "  " + info.getRAMInformation().getModulesRAM()[i].bank  +
    //        "  " + std::to_string(info.getRAMInformation().getModulesRAM()[i].ramSize/1024/1024/1024) + "gb" +
    //        "  " + std::to_string(info.getRAMInformation().getModulesRAM()[i].speed) + "MHz" << endl;

    //}
    //cout << "  Memory RAM size: " + info.getRAMInformation().getMemoryRAMsize_Win32() + "gb" << endl;
    //cout << "____________________________________________________\n" << endl;

    //cout << "  BIOS:" << endl;
    //cout << "  " + info.getBIOSInformation().getManufacturer() + "\n" +
    //    "  " + info.getBIOSInformation().getName() + "\n" +
    //    "  " + info.getBIOSInformation().getVersion() + "\n" +
    //    "  Serial Number - " + info.getBIOSInformation().getSerialNumber() << endl;

    //cout << "____________________________________________________\n\n" << endl;

    system("pause"); 
    return 0;
}

