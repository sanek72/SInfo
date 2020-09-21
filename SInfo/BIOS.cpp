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

	std::vector< string > properties;

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

			cout << "\t" << getManufacturer() << endl;
			cout << "\t" << getName() << endl;
			cout << "\t" << getVersion() << endl;
			cout << "\t" << getSerialNumber() << endl << endl;


	}
	else {
		//erore
		cout << typeid(BIOS).name() << ". Error getting information." << endl;
	}

}


//template< typename T, std::size_t N >
//void BIOS::receiving(std::array<T, N>& v, std::string _class_name) {
//	size_t len = v.size();
//
//	std::vector< std::string > properties;
//
//	for (size_t i = 0; i < len; ++i) {
//		properties.push_back(v[i]);
//	}
//
//	std::vector< std::string > value;
//
//	if (InitializesCOM(OBJECTPATH, WQL + _class_name, properties).Initialize(value)) {
//
//		//work
//		for (size_t i = 0; i < properties.size(); ++i) {
//
//			//std::cout << "Class[" + _class_name + "] propertie[" + properties[i] + "] = " + value[i] << std::endl;
//
//			if (properties[i] == "Manufacturer") {
//				setManufacturer(value[i]);
//			}
//
//			if (properties[i] == "Name") {
//				setName(value[i]);
//			}
//
//			if (properties[i] == "SerialNumber") {
//				setSerialNumber(value[i]);
//
//			}
//
//			if (properties[i] == "Version") {
//				setVersion(value[i]);
//			}
//
//		}
//
//		}else {
//		//erore
//		std::cout << typeid(BIOS).name() << ". Error getting information." << std::endl;
//	
//
//	}
//
//	}

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