#include "GPU.h"

GPU::GPU(bool WMIRequest) {

	if (WMIRequest) {
		static const string VIDEOCONTROLLER_CLASS = "Win32_VideoController";	
		static const int VIDEOCONTROLLER_SIZE = 6;
		array<string, VIDEOCONTROLLER_SIZE> videoController = { "Name", "DriverDate", "DriverVersion", "AdapterCompatibility", "VideoProcessor", "AdapterRAM" };
		receiving(videoController, VIDEOCONTROLLER_CLASS);
	}

}

template< typename T, size_t N >
void GPU::receiving(array<T, N>& v, string _class_name) {
		size_t len = v.size();
	
		vector< string > properties;
	
		for (size_t i = 0; i < len; ++i) {
			properties.push_back(v[i]);
		}

		DataWork dataWork;
		
		InitializesCOM initCom;

		if (initCom.Initialize(OBJECTPATH, WQL + _class_name, properties, dataWork)) {

			//work
			setAdapterCount(dataWork.data_count);

			for (int i = 1; i <= dataWork.data_count; ++i) {

				ADAPTER a;
					
				a.videoCardName = dataWork.getDataString("Name" + to_string(i));
				a.driverDate = dataWork.getDataString("DriverDate" + to_string(i));
				a.driverVersion = dataWork.getDataString("DriverVersion" + to_string(i));
				a.adapterCompatibility = dataWork.getDataString("AdapterCompatibility" + to_string(i));
				a.videoProcessor = dataWork.getDataString("VideoProcessor" + to_string(i));
				a.ramSize = dataWork.getDataLongLong("AdapterRAM" + std::to_string(i));

				adapter_bufer.push_back(a);

			}

		} else {
			//erore
			cout << typeid(GPU).name() << ". Error getting information." << endl;
		}

}


string GPU::getGPUName_WinAPI() {
    DISPLAY_DEVICEA dd;
    dd.cb = sizeof(DISPLAY_DEVICEA);
    EnumDisplayDevicesA(NULL, 0, &dd, EDD_GET_DEVICE_INTERFACE_NAME);
    return string(dd.DeviceString);
}

vector<GPU::ADAPTER> GPU::getADAPTERS() {
	return adapter_bufer;
}

int GPU::getAdapteCount(){
	return adapterCount;
}

void GPU::setAdapterCount(int _adapterCount){
	adapterCount = _adapterCount;
}

