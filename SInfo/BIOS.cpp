#include "BIOS.h"

BIOS::BIOS(bool WMIRequest) {

	if (WMIRequest) {
		const int BIOS_SIZE = 4;
		const string BIOS_CLASS = "Win32_BIOS";
		array<string, BIOS_SIZE> bios = { "Manufacturer", "Name", "SerialNumber", "Version" };
		receiving(bios, BIOS_CLASS);
	}

}

template< typename T, size_t N >
void BIOS::receiving(array<T, N>& v, string _class_name) {

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

			setManufacturer(dataWork.getDataString("Manufacturer" + to_string(i)));
			setName(dataWork.getDataString("Name" + to_string(i)));
			setSerialNumber(dataWork.getDataString("SerialNumber" + to_string(i)));
			setVersion(dataWork.getDataString("Version" + to_string(i)));

		}

	} else {
		//erore
		cout << typeid(BIOS).name() << ". Error getting information." << endl;
	}

}

void BIOS::setManufacturer(string _manufacturer){
	manufacturer = _manufacturer;
}

void BIOS::setName(string _name){
	name = _name;
}

void BIOS::setVersion(string _version){
	version = _version;
}

void BIOS::setSerialNumber(string _serialNumber){
	serialNumber = _serialNumber;
}

string BIOS::getManufacturer(){
	return manufacturer;
}

string BIOS::getName(){
	return name;
}

string BIOS::getVersion(){
	return version;
}

string BIOS::getSerialNumber(){
	return serialNumber;
}