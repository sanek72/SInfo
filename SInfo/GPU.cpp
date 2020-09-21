#include "GPU.h"

GPU::GPU(bool WMIRequest) {
	cout << "\t" << "GPU::GPU(bool WMIRequest)"<< endl;
	if (WMIRequest) {
		static const string videoController_class = "Win32_VideoController";
		static const int videoController_size = 6;
		array<string, videoController_size> videoController = { "Name", "DriverDate", "DriverVersion", "AdapterCompatibility", "VideoProcessor", "AdapterRAM" };

		receiving(videoController, videoController_class);
	}

}

template< typename T, size_t N >
void GPU::receiving(array<T, N>& v, string _class_name) {
		size_t len = v.size();
	
		std::vector< string > properties;
	
		for (size_t i = 0; i < len; ++i) {
			properties.push_back(v[i]);
		}

		DataWork dataWork;
		
		InitializesCOM initCom;

		if (initCom.Initialize(ObjectPath, WQL + _class_name, properties, dataWork)) {

			//work
			for (int i = 1; i <= dataWork.data_count; ++i) {

				ADAPTER a;
					
				a.videoCardName = dataWork.getDataString("Name" + to_string(i));
				a.driverDate = dataWork.getDataString("DriverDate" + to_string(i));
				a.driverVersion = dataWork.getDataString("DriverVersion" + to_string(i));
				a.adapterCompatibility = dataWork.getDataString("AdapterCompatibility" + to_string(i));
				a.videoProcessor = dataWork.getDataString("VideoProcessor" + to_string(i));
				a.ramSize = dataWork.getDataLong("AdapterRAM" + std::to_string(i));

				adapter_bufer.push_back(a);

			}

			for (ADAPTER a : adapter_bufer) {
				cout << "\t" << a.videoCardName << endl;
				cout << "\t" << a.adapterCompatibility << endl;
				cout << "\t" << a.ramSize / 1024 / 1024 << endl << endl;
			}

		} else {
			//erore
			cout << typeid(GPU).name() << ". Error getting information." << endl;
		}

}


string GPU::getGPUName_Win32() {
    DISPLAY_DEVICEA dd;
    dd.cb = sizeof(DISPLAY_DEVICEA);
    EnumDisplayDevicesA(NULL, 0, &dd, EDD_GET_DEVICE_INTERFACE_NAME);
    return string(dd.DeviceString);
}

vector<GPU::ADAPTER> GPU::getADAPTERS() {
	return adapter_bufer;
}
