#include "Sound.h"

Sound::Sound(bool WMIRequest) {

    if (WMIRequest) {
        static const int SOUNDDEVICE_SIZE = 2;
        static const string SOUNDDEVIC_CLASS = "Win32_SoundDevice";
        array<string, SOUNDDEVICE_SIZE> soundDevice = { "Manufacturer", "Name" };
        receiving(soundDevice, SOUNDDEVIC_CLASS);
    }

}

template< typename T, size_t N >
void Sound::receiving(array<T, N>& v, string _class_name) {
	size_t len = v.size();

	vector< string > properties;

	for (size_t i = 0; i < len; ++i) {
		properties.push_back(v[i]);
	}

	DataWork dataWork;

	InitializesCOM initCom;

	if (initCom.Initialize(OBJECTPATH, WQL + _class_name, properties, dataWork)) {

		//work
		setDeviceCount(dataWork.data_count);

		for (int i = 1; i <= dataWork.data_count; ++i) {

			DEVICE d;

			d.manufacturer = dataWork.getDataString("Manufacturer" + to_string(i));
			d.name = dataWork.getDataString("Name" + to_string(i));

			device_bufer.push_back(d);

		}

	}
	else {
		//erore
		cout << typeid(Sound).name() << ". Error getting information." << endl;
	}

}

int Sound::getDeviceCount() {
    return deviceCount;
}

vector<Sound::DEVICE> Sound::getDevice() {
    return device_bufer;
}


void Sound::setDeviceCount(int _deviceCount) {
    deviceCount = _deviceCount;
}