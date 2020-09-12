#include "GPU.h"



GPU::GPU() {

	static const int videoController_size = 59;
	static const std::string videoController_class = "Win32_VideoController";
	std::array<std::string, videoController_size> videoController = { "AcceleratorCapabilities", "AdapterCompatibility", "AdapterDACType", "AdapterRAM", "Availability", "CapabilityDescriptions", "Caption",
		"ColorTableEntries", "ConfigManagerErrorCode", "ConfigManagerUserConfig", "CreationClassName", "CurrentBitsPerPixel", "CurrentHorizontalResolution", "CurrentNumberOfColors", "CurrentNumberOfColumns", 
		"CurrentNumberOfRows", "CurrentRefreshRate", "CurrentScanMode", "CurrentVerticalResolution", "Description", "DeviceID", "DeviceSpecificPens", "DitherType", "DriverDate", "DriverVersion", "ErrorCleared", 
		"ErrorDescription", "ICMIntent", "ICMMethod", "InfFilename", "InfSection", "InstallDate", "InstalledDisplayDrivers", "LastErrorCode", "MaxMemorySupported", "MaxNumberControlled", "MaxRefreshRate",
		"MinRefreshRate", "Monochrome", "Name", "NumberOfColorPlanes", "NumberOfVideoPages", "PNPDeviceID", "PowerManagementCapabilities", "PowerManagementSupported", "ProtocolSupported", 
		"ReservedSystemPaletteEntries", "SpecificationVersion", "Status", "StatusInfo", "SystemCreationClassName", "SystemName", "SystemPaletteEntries", "TimeOfLastReset", "VideoArchitecture",
		"VideoMemoryType", "VideoMode", "VideoModeDescription", "VideoProcessor" };

	if (!isInit) {

		receiving(videoController, videoController_class);
		GPU::isInit = true;

	}

}

template< typename T, std::size_t N >
void GPU::receiving(std::array<T, N>& v, std::string _class_name) {
	size_t len = v.size();

	std::vector< std::string > properties;

	for (size_t i = 0; i < len; ++i) {
		properties.push_back(v[i]);
	}


	InitializesCOM* initCOM;

	initCOM = new InitializesCOM(ObjectPath, WQL + _class_name, properties);

	std::vector< std::string > value;

	if (initCOM->Initialize(value)) {

		size_t all = value.size();

		std::cout << "Class[ " + std::to_string(all) << std::endl;

		//work
		for (size_t i = 0; i < properties.size(); ++i) {

		    //std::cout << "Class[" + _class_name + "] propertie[" + properties[i] + "] = " + value[i] << std::endl;

			if (properties[i] == "Name") {

				setVideoCardName(value[i]);

			}

			if (properties[i] == "InstalledDisplayDrivers") {

				setInstalledDisplayDrivers(value[i]);

			}

			if (properties[i] == "DriverDate") {

				setDriverDate(value[i]);

			}

			if (properties[i] == "DriverVersion") {

				setDriverVersion(value[i]);

			}

			if (properties[i] == "AdapterCompatibility") {

				setAdapterCompatibility(value[i]);

			}

			if (properties[i] == "VideoProcessor") {

				setVideoProcessor(value[i]);

			}

			if (properties[i] == "AdapterRAM") {

				setRamSize(value[i]);

			}
		}

	} else {
		//erore
		std::cout << typeid(GPU).name() << ". Error getting information." << std::endl;
	}

	delete(initCOM);
	
}

std::string GPU::getGPUName_Win32() {
    DISPLAY_DEVICEA dd;
    dd.cb = sizeof(DISPLAY_DEVICEA);
    EnumDisplayDevicesA(NULL, 0, &dd, EDD_GET_DEVICE_INTERFACE_NAME);
    return std::string(dd.DeviceString);
}

std::string GPU::getVideoCardName(){
	return videoCardName;
}

std::string GPU::getDriverVersion(){
	return driverVersion;
}

std::string GPU::getDriverDate(){
	return driverDate;
}

std::string GPU::getAdapterCompatibility() {
	return adapterCompatibility;
}

std::string GPU::getVideoProcessor(){
	return videoProcessor;
}

std::vector<std::string> GPU::getInstalledDisplayDrivers(){
	return installedDisplayDrivers;
}

long long GPU::getRamSize(){
	return ramSize;
}

void GPU::setVideoCardName(std::string _videoCardName){
	videoCardName = _videoCardName;
}

void GPU::setDriverVersion(std::string _driverVersion){
	driverVersion = _driverVersion;
}

void GPU::setDriverDate(std::string _driverDate){
	driverDate = _driverDate;
}

void GPU::setAdapterCompatibility(std::string _adapterCompatibility){
	adapterCompatibility = _adapterCompatibility;
}

void GPU::setVideoProcessor(std::string _videoProcessor){
	videoProcessor = _videoProcessor;
}

void GPU::setInstalledDisplayDrivers(std::string _displayDrivers){
	return;
	if (_displayDrivers.size() == 0 || _displayDrivers == "unavailable") {
		return;
	}

	std::istringstream ss(_displayDrivers);
	std::string token;

	while (std::getline(ss, token, ',')) {
		installedDisplayDrivers.push_back(token);
	}
}

void GPU::setRamSize(std::string _ramSize){
	if (_ramSize == "unavailable") {
		return;
	}
	ramSize = std::stoll(_ramSize);
}
