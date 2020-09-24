#include "OS.h"


OS::OS(bool WMIRequest) {

	if (WMIRequest) {
		static const int OPERATINGSYSTEM_SIZE = 6;
		static const string OPERATINGSYSTEM_CLASS = "Win32_OperatingSystem";
		array<string, OPERATINGSYSTEM_SIZE> OperatingSystem = { "Caption", "CSName", "BuildNumber", "OSArchitecture", "LocalDateTime", "RegisteredUser" };
		receiving(OperatingSystem, OPERATINGSYSTEM_CLASS);
	}

}

template< typename T, size_t N >
void OS::receiving(array<T, N>& v, string _class_name) {

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

			setOSName(dataWork.getDataString("Caption" + to_string(i)));
			setComputerName(dataWork.getDataString("CSName" + to_string(i)));
			setBuildNumber(dataWork.getDataString("BuildNumber" + to_string(i)));
			setOSArchitecture(dataWork.getDataString("OSArchitecture" + to_string(i)));
			setLocalDateTime(dataWork.getDataString("LocalDateTime" + to_string(i)));
			setRegisteredUser(dataWork.getDataString("RegisteredUser" + to_string(i)));

		}

	} else {
		//erore
		cout << typeid(OS).name() << ". Error getting information." << endl;
	}

}

string OS::getComputerName_WinAPI(){

	string s = "unavailable";
	char buffer[256];
	DWORD size = 256;

	if (GetComputerNameA(buffer, &size)) {

		s = buffer;
		return s;

	} else {

		cout << typeid(OS).name() << ". Error getting information. " << GetLastError() << endl;
		return s;

	}
	return s;

}

string OS::getOSName_WinAPI() {

	string s = "unavailable";
	OSVERSIONINFOEX info;
	ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
	info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
#pragma warning(disable : 4996)
	if (GetVersionEx((LPOSVERSIONINFO)&info)) {

		if (info.dwMajorVersion == 10 && info.dwMinorVersion == 0) {
			return "Windows 10 (bulid: " + to_string(info.dwBuildNumber) + ")";
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

		cout << typeid(OS).name() << ". Error getting information. " << GetLastError() << endl;
		return s;

	}

	return s;

	}

string OS::getOSName(){
	return OSName;
}

void OS::setOSName(string _OSName){
	OSName = _OSName;
}

string OS::getComputerName(){
	return сomputerName;
}

void OS::setComputerName(string _сomputerName){
	сomputerName = _сomputerName;
}

string OS::getBuildNumber() {
	return buildNumber;
}

void OS::setBuildNumber(string _buildNumber) {
	buildNumber = _buildNumber;
}


string OS::getOSArchitecture() {
	return OSArchitecture;
}

void OS::setOSArchitecture(string _OSArchitecture) {
	OSArchitecture = _OSArchitecture;
}

string OS::getLocalDateTime() {
	return localDateTime;
}

void OS::setLocalDateTime(string _localDateTime) {
	localDateTime = _localDateTime;
}

string OS::getRegisteredUser() {
	return registeredUser;
}

void OS::setRegisteredUser(string _registeredUser) {
	registeredUser = _registeredUser;
}

string OS::getUserNameEx() {

	string s = "unavailable";
	unsigned long Size = 256;
	char* buffer = new char[Size];

	//    NameSamCompatible - A legacy account name (for example, Engineering\JSmith). The domain-only version includes trailing backslashes (\).
	//    NameDisplay - A "friendly" display name (for example, Jeff Smith). The display name is not necessarily the defining relative distinguished name (RDN).
	//    NameGivenName - user name
	//    NameSurname

	if (GetUserNameExA(NameGivenName, buffer, &Size)) {

		s = buffer;
		return s;

	} else {

		cout << typeid(OS).name() << ". Error getting information. " << GetLastError() << endl;
		return s;

	}
	return s;

}

string OS::getUserName() {

	string s = "unavailable";
	unsigned long Size = 256;
	char* buffer = new char[Size];
	if (GetUserNameA(buffer, &Size)) {

		s = buffer;
		return s;

	}else {

		cout << typeid(OS).name() << ". Error getting information. " << GetLastError() << endl;
		return s;

	}
	return s;

}