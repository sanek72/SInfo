#include "BIOS.h"

BIOS::BIOS() {
	static const int bios_size = 31;
	static const std::string bios_class = "Win32_BIOS";
	std::array<std::string, bios_size> BIOS = { "BiosCharacteristics", "BIOSVersion", "BuildNumber", "Caption", "CodeSet", "CurrentLanguage", "Description", "EmbeddedControllerMajorVersion",
		"EmbeddedControllerMinorVersion", "IdentificationCode", "InstallableLanguages", "InstallDate", "LanguageEdition", "ListOfLanguages", "Manufacturer", "Name", "OtherTargetOS",
		"PrimaryBIOS", "ReleaseDate", "SerialNumber", "SMBIOSBIOSVersion", "SMBIOSMajorVersion", "SMBIOSMinorVersion", "SMBIOSPresent", "SoftwareElementID", "SoftwareElementState", "Status",
		"SystemBiosMajorVersion", "SystemBiosMinorVersion", "TargetOperatingSystem", "Version" };

		receiving(BIOS, bios_class);

}

template< typename T, std::size_t N >
void BIOS::receiving(std::array<T, N>& v, std::string _class_name) {
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

			if (properties[i] == "Manufacturer") {
				setManufacturer(value[i]);
			}

			if (properties[i] == "Name") {
				setName(value[i]);
			}

			if (properties[i] == "SerialNumber") {
				setSerialNumber(value[i]);

			}

			if (properties[i] == "Version") {
				setVersion(value[i]);
			}

		}

		}else {
		//erore
		std::cout << typeid(BIOS).name() << ". Error getting information." << std::endl;
	

	}

	}

void BIOS::setManufacturer(std::string _manufacturer){
	manufacturer = _manufacturer;
}

void BIOS::setName(std::string _name){
	name = _name;
}

void BIOS::setVersion(std::string _version){
	version = _version;
}

void BIOS::setSerialNumber(std::string _serialNumber){
	serialNumber = _serialNumber;
}

std::string BIOS::getManufacturer()
{
	return manufacturer;
}

std::string BIOS::getName()
{
	return name;
}

std::string BIOS::getVersion()
{
	return version;
}

std::string BIOS::getSerialNumber()
{
	return serialNumber;
}