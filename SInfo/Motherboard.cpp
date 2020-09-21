#include "Motherboard.h"

Motherboard::Motherboard(bool WMIRequest) {

	if (WMIRequest) {
		static const int BASEBOARDE_SIZE = 3;
		static const string BASEBOARDE_CLASS = "Win32_BaseBoard";
		array<string, BASEBOARDE_SIZE> BaseBoard = { "Manufacturer", "Product", "SerialNumber" };
		receiving(BaseBoard, BASEBOARDE_CLASS);
	}

}

template< typename T, size_t N >
void Motherboard::receiving(array<T, N>& v, string _class_name) {

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
			setProduct(dataWork.getDataString("Product" + to_string(i)));
			setSerialNumber(dataWork.getDataString("SerialNumber" + to_string(i)));

		}

	} else {
		//erore
		cout << typeid(Motherboard).name() << ". Error getting information." << endl;
	}

}

string Motherboard::getManufacturer() {
	return manufacturer;
}

void Motherboard::setManufacturer(string _manufacturer) {
	manufacturer = _manufacturer;
}

string Motherboard::getProduct() {
	return product;
}

void Motherboard::setProduct(string _product) {
	product = _product;
}

string Motherboard::getSerialNumber() {
	return serialNumber;
}

void Motherboard::setSerialNumber(string _serialNumber) {
	serialNumber = _serialNumber;
}

