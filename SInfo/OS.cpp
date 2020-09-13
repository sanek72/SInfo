#include "OS.h"


OS::OS() {

	static const int operatingSystem_size = 64;
	static const std::string operatingSystem_class = "Win32_OperatingSystem";
	std::array<std::string, operatingSystem_size> OperatingSystem = { "BootDevice", "BuildNumber", "BuildType", "Caption", "CodeSet", "CountryCode", "CreationClassName", "CSDVersion", "CSName", "CurrentTimeZone", "Name",
	"DataExecutionPrevention_Available", "DataExecutionPrevention_32BitApplications", "DataExecutionPrevention_Drivers", "DataExecutionPrevention_SupportPolicy", "Debug", "Description",
	"Distributed", "EncryptionLevel", "ForegroundApplicationBoost", "FreePhysicalMemory", "FreeSpaceInPagingFiles", "FreeVirtualMemory", "InstallDate", "LargeSystemCache", "LastBootUpTime",
		"LocalDateTime", "Locale", "Manufacturer", "MaxNumberOfProcesses", "MaxProcessMemorySize", "MUILanguages", "NumberOfLicensedUsers", "NumberOfProcesses", "OperatingSystemSKU",
	"Organization", "OSArchitecture", "OSLanguage", "OSProductSuite", "OSType", "OtherTypeDescription", "PAEEnabled", "PlusProductID", "PlusVersionNumber", "PortableOperatingSystem", "Primary", 
		"ProductType", "QuantumLength", "QuantumType", "RegisteredUser", "SerialNumber", "ServicePackMajorVersion", "ServicePackMinorVersion", "SizeStoredInPagingFiles", "Status", "SuiteMask", 
		"SystemDevice", "SystemDirectory", "SystemDrive", "TotalSwapSpaceSize", "TotalVirtualMemorySize", "TotalVisibleMemorySize", "Version", "WindowsDirectory" };

		receiving(OperatingSystem, operatingSystem_class);

}

template< typename T, std::size_t N >
void OS::receiving(std::array<T, N>& v, std::string _class_name) {

	size_t len = v.size();

	std::vector< std::string > properties;

	for (size_t i = 0; i < len; ++i) {
		properties.push_back(v[i]);
	}

	std::vector< std::string > value;

	if (InitializesCOM(ObjectPath, WQL + _class_name, properties).Initialize(value)) {

		//work
		for (size_t i = 0; i < properties.size(); ++i) {

			//std::cout << "Class[" + _class_name + "] propertie[" + properties[i] + "] = " + value[i] << std::endl;

			if (properties[i] == "Caption") {

				setOSName(value[i]);

			}

			if (properties[i] == "CSName") {

				setComputerName(value[i]);

			}

			if (properties[i] == "BuildNumber") {

				setBuildNumber(value[i]);

			}

			//if (properties[i] == "FreePhysicalMemory") {

			//	setFreePhysicalMemory(value[i]);

			//}

			if (properties[i] == "OSArchitecture") {

				setOSArchitecture(value[i]);

			}

			if (properties[i] == "LocalDateTime") {

				setLocalDateTime(value[i]);

			}

			if (properties[i] == "RegisteredUser") {

				setRegisteredUser(value[i]);

			}

		}

	}
	else {
		//erore
		std::cout << typeid(OS).name() << ". Error getting information." << std::endl;
	}

}


std::string OS::getComputerName_Win32(){

	char buffer[256];
	DWORD size = 256;

	if (GetComputerNameA(buffer, &size)) {

		return buffer;

	} else {

    printf(typeid(OS).name() ,". Error getting information.");
		printf("%d\n", GetLastError());
		return "NULL";

	}
	return "NULL";

}

std::string OS::getOSName_Win32() {

	OSVERSIONINFOEX info;
	ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
#pragma warning(disable : 4996)
	if (GetVersionEx((LPOSVERSIONINFO)&info)) {

		if (info.dwMajorVersion == 10 && info.dwMinorVersion == 0) {
			return "Windows 10 (bulid: " + std::to_string(info.dwBuildNumber) + ")";
		}
		if (info.dwMajorVersion == 6 && info.dwMinorVersion == 3) {
			return "Windows 8.1";
		}
		if (info.dwMajorVersion == 6 && info.dwMinorVersion == 2) {
			return "Windows 8";
		}
		if (info.dwMajorVersion == 6 && info.dwMinorVersion == 1) {
			return "Windows 7";
		}
		if (info.dwMajorVersion == 6 && info.dwMinorVersion == 0) {
			return "Windows Vista";
		}
		if (info.dwMajorVersion == 5 && info.dwMinorVersion == 2) {
			return "Windows XP Professional x64 Edition";
		}
		if (info.dwMajorVersion == 5 && info.dwMinorVersion == 1) {
			return "Windows XP";
		}
		if (info.dwMajorVersion == 5 && info.dwMinorVersion == 0) {
			return "Windows 2000";
		}

	} else {

		printf(typeid(OS).name(), ". Error getting information.");
		printf("%d\n", GetLastError());
		return "NULL";

	}

	return "NULL";

	}

std::string OS::getOSName(){

	return OSName;

}

void OS::setOSName(std::string _OSName){
	OSName = _OSName;
}

std::string OS::getComputerName(){
	return сomputerName;
}

void OS::setComputerName(std::string _сomputerName){
	сomputerName = _сomputerName;
}

std::string OS::getBuildNumber() {
	return buildNumber;
}

void OS::setBuildNumber(std::string _buildNumber) {
	buildNumber = _buildNumber;
}

//int OS::getFreePhysicalMemory() {
//	return freePhysicalMemory;
//}
//
//void OS::setFreePhysicalMemory(std::string _freePhysicalMemory) {
//	freePhysicalMemory = std::stoi(_freePhysicalMemory);
//}

std::string OS::getOSArchitecture() {
	return OSArchitecture;
}

void OS::setOSArchitecture(std::string _OSArchitecture) {
	OSArchitecture = _OSArchitecture;
}

std::string OS::getLocalDateTime() {
	return localDateTime;
}

void OS::setLocalDateTime(std::string _localDateTime) {
	localDateTime = _localDateTime;
}

std::string OS::getRegisteredUser() {
	return registeredUser;
}

void OS::setRegisteredUser(std::string _registeredUser) {
	registeredUser = _registeredUser;
}

std::string OS::getUserNameEx() {

	unsigned long Size = 256;
	char* buffer = new char[Size];

	//    NameSamCompatible - A legacy account name (for example, Engineering\JSmith). The domain-only version includes trailing backslashes (\).
	//    NameDisplay - A "friendly" display name (for example, Jeff Smith). The display name is not necessarily the defining relative distinguished name (RDN).
	//    NameGivenName - user name
	//    NameSurname

	if (GetUserNameExA(NameGivenName, buffer, &Size)) {

		return buffer;

	}
	else {

		printf("ERORE. Failed to GetUserNameEx: ");
		printf("%d\n", GetLastError());
		return "NULL";

	}
	return "NULL";
}

std::string OS::getUserName() {
	unsigned long Size = 256;
	char* buffer = new char[Size];
	if (GetUserNameA(buffer, &Size)) {

		return buffer;

	}
	else {

		printf("ERORE. Failed to GetUserNameEx: ");
		printf("%d\n", GetLastError());
		return "NULL";

	}
	return "NULL";
}