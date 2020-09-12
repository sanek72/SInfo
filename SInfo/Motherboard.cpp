#include "Motherboard.h"

Motherboard::Motherboard(){

	static const int MotherboardDevice_size = 22;
	static const std::string motherboardDevice_class = "Win32_MotherboardDevice";
	std::array<std::string, MotherboardDevice_size> MotherboardDevice = { "Availability" , "Caption", "ConfigManagerErrorCode", "ConfigManagerUserConfig", "CreationClassName",
	   "Description", "DeviceID", "ErrorCleared", "ErrorDescription", "InstallDate", "LastErrorCode", "Name", "PNPDeviceID", "PowerManagementCapabilities", "PowerManagementSupported",
	   "PrimaryBusType", "RevisionNumber", "SecondaryBusType", "Status", "StatusInfo", "SystemCreationClassName", "SystemName" };

	static const int BaseBoarde_size = 29;
	static const std::string baseBoard_class = "Win32_BaseBoard";
	std::array<std::string, BaseBoarde_size> BaseBoard = { "Caption", "ConfigOptions", "CreationClassName", "Depth", "Description", "Height", "HostingBoard", "HotSwappable", "InstallDate",
	   "Manufacturer", "Model", "Name", "OtherIdentifyingInfo", "PartNumber", "PoweredOn", "Product", "Removable", "Replaceabl", "RequirementsDescription",
	   "RequiresDaughterBoard", "SerialNumber", "SKU", "SlotLayout", "SpecialRequirements", "Status", "Tag", "Version", "Weight", "Width" };


	if (!isInit) {
		
		receiving(BaseBoard, baseBoard_class);
		//receiving(MotherboardDevice, motherboardDevice_class);
		Motherboard::isInit = true;
		
	}

}

template< typename T, std::size_t N >
void Motherboard::receiving( std::array<T, N> &v, std::string _class_name)  {

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

				//std::cout << "Clas[" + _class_name + "] propertie[" + properties[i] + "] = " + value[i]<< std::endl;

				if (properties[i] == "Manufacturer") {

					setManufacturer(value[i]);

				}

				if (properties[i] == "Product") {

					setProduct(value[i]);

				}

				if (properties[i] == "SerialNumber") {

					setSerialNumber(value[i]);

				}
			}

		}else {
			//erore
			std::cout << typeid(Motherboard).name() << ". Error getting information." << std::endl;
		}

		delete(initCOM);
}


std::string Motherboard::getManufacturer() {
	return manufacturer;
}

void Motherboard::setManufacturer(std::string _manufacturer) {
	manufacturer = _manufacturer;
}

std::string Motherboard::getProduct() {
	return product;
}

void Motherboard::setProduct(std::string _product) {
	product = _product;
}

std::string Motherboard::getSerialNumber() {
	return serialNumber;
}

void Motherboard::setSerialNumber(std::string _serialNumber) {
	serialNumber = _serialNumber;
}

