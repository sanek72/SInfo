#include "Network.h"

Network::Network(bool WMIRequest) {

    if (WMIRequest) {
        static const int NETWORKADAPTER_SIZE = 4;
        static const string NETWORKADAPTER_CLASS = "Win32_NetworkAdapter";
        array<string, NETWORKADAPTER_SIZE> networkAdaper = { "Manufacturer", "Name", "MACAddress", "NetEnabled" };
        receiving(networkAdaper, NETWORKADAPTER_CLASS);
    }

}

template< typename T, size_t N >
void Network::receiving(array<T, N>& v, string _class_name) {
	size_t len = v.size();

	vector< string > properties;

	for (size_t i = 0; i < len; ++i) {
		properties.push_back(v[i]);
	}

	DataWork dataWork;

	InitializesCOM initCom;

	if (initCom.Initialize(OBJECTPATH, WQL + _class_name + FILTER_WQL, properties, dataWork)) {

		//work
		setAdapterCount(dataWork.data_count);

		for (int i = 1; i <= dataWork.data_count; ++i) {

			ADAPTER a;

			a.manufacturer = dataWork.getDataString("Manufacturer" + to_string(i));
			a.name = dataWork.getDataString("Name" + to_string(i));
			a.MACAddress = dataWork.getDataString("MACAddress" + to_string(i));
			a.netEnabled = dataWork.getDataBoolean("NetEnabled" + to_string(i));

			adapter_bufer.push_back(a);

		}

	} else {
		//erore
		cout << typeid(Network).name() << ". Error getting information." << endl;
	}

}

int Network::getAdapterCount() {
    return adapterCount;
}

vector<Network::ADAPTER> Network::getAdapters() {
    return adapter_bufer;
}

void Network::setAdapterCount(int _adapterCount) {
    adapterCount = _adapterCount;
}
