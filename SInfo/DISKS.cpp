#include "DISKS.h"


DISKS::DISKS(bool WMIRequest) {

	if (WMIRequest) {
		// физические диски
		static const int DISKDRIVE_SIZE = 5;
		array<string, DISKDRIVE_SIZE> diskDrive = { "Model", "Size", "SerialNumber", "InterfaceType", "Name" };
		receiving(diskDrive, DISKDRIVE_CLASS);
		// логические диски
		static const int LOGICAL_SIZE = 5;
		array<string, LOGICAL_SIZE> logicalDisk = { "Name", "FreeSpace", "Size", "FileSystem", "DriveType" };
		receiving(logicalDisk, LOGICALDISK_CLASS);
	}

}

template<typename T, size_t N>
 void DISKS::receiving(array<T, N>& v, string _class_name){
	size_t len = v.size();

	vector< string > properties;

	for (size_t i = 0; i < len; ++i) {
		properties.push_back(v[i]);
	}

	DataWork dataWork;

	InitializesCOM initCom;

	if (initCom.Initialize(OBJECTPATH, WQL + _class_name, properties, dataWork)) {

		//work
		if (_class_name == DISKDRIVE_CLASS) {

			setFhysicalDiskCount(dataWork.data_count);

			for (int i = 1; i <= dataWork.data_count; ++i) {

				PHYSICALDISK fd;
				fd.model = dataWork.getDataString("Model" + to_string(i));
				fd.size = dataWork.uint64ToLongLong(dataWork.getDataString("Size" + std::to_string(i)));
				fd.serialNumber = dataWork.getDataString("SerialNumber" + to_string(i));
				fd.interfaceType = dataWork.getDataString("InterfaceType" + to_string(i));
				fd.name = dataWork.getDataString("Name" + to_string(i));
				fdisk_bufer.push_back(fd);

			}

		}

		if (_class_name == LOGICALDISK_CLASS) {

			setLogicalDiskCount(dataWork.data_count);

			for (int i = 1; i <= dataWork.data_count; ++i) {

				LOGICALDISK ld;
				ld.name = dataWork.getDataString("Name" + to_string(i));
				ld.free_size = dataWork.uint64ToLongLong(dataWork.getDataString("FreeSpace" + std::to_string(i)));
				ld.size = dataWork.uint64ToLongLong(dataWork.getDataString("Size" + std::to_string(i)));
				ld.fileSystem = dataWork.getDataString("FileSystem" + to_string(i));
				ld.type = dataWork.getDataLong("DriveType" + to_string(i));
				ldisk_bufer.push_back(ld);
			}

		}
		
	} else {
		//erore
		cout << typeid(DISKS).name() << ". Error getting information." << endl;
	}

}


	vector< DISKS::PHYSICALDISK > DISKS::getFDisks() {
		return fdisk_bufer;
	}

	vector< DISKS::LOGICALDISK > DISKS::getLDisks() {
		return ldisk_bufer;
	}

	int DISKS::getFhysicalDiskCount(){
		return fhysicalDiskCount;
	}

	int DISKS::getLogicalDiskCount() {
		return logicalDiskCount;
	}

	void DISKS::setFhysicalDiskCount(int _fhysicalDiskCount) {
		fhysicalDiskCount = _fhysicalDiskCount;
	}

	void DISKS::setLogicalDiskCount(int _logicalDiskCount) {
		logicalDiskCount = _logicalDiskCount;
	}

	vector< string > DISKS::getLogicaDisk() {
		vector< string > list;
		char buffer[256];
		DWORD sizebuf = 256;
		char* disk;
		DWORD v = GetLogicalDriveStringsA(sizebuf, buffer);
		if (v > 0 && v <= sizebuf){
			disk = buffer;
			while (*disk) {
				list.push_back(disk);
				disk += strlen(disk) + 1;
			}
		}
		return list;
	}

	long long DISKS::getLogicaDiskTotalSize(string _drive) {

		long long v = 0;
		std::wstring temp = Utils::s2ws(_drive);
		LPCWSTR drive = temp.c_str();
		ULARGE_INTEGER totalNumberOfBytes;

		if (GetDiskFreeSpaceEx(drive, NULL, &totalNumberOfBytes, NULL)) {

			v = totalNumberOfBytes.QuadPart;

		} else {

			cout << typeid(DISKS).name() << ". Error getting information. " << GetLastError() << endl;

		}

		return v;
	}

	long long DISKS::getLogicaDiskFreeSize(string _drive) {

		long long v = 0;
		std::wstring temp = Utils::s2ws(_drive);
		LPCWSTR drive = temp.c_str();
		ULARGE_INTEGER freeNumberOfBytes;

		if (GetDiskFreeSpaceEx(drive, NULL, NULL, &freeNumberOfBytes)) {

			v = freeNumberOfBytes.QuadPart;

		} else {

			cout << typeid(DISKS).name() << ". Error getting information. " << GetLastError() << endl;

		}

		return v;

	}

	string DISKS::getLogicaDiskType(string _drive) {

		std::wstring temp = Utils::s2ws(_drive);
		LPCWSTR drive = temp.c_str();
		return getDiskTypeString(GetDriveType(drive));
	}

	string DISKS::getDiskTypeString(int _type) {

		string v;

		switch (_type) {
		case DRIVE_UNKNOWN:
			v = "The drive type cannot be determined.";
			break;
		case DRIVE_NO_ROOT_DIR:
			v = "The root path is invalid";
			break;
		case DRIVE_REMOVABLE:
			v = "The drive has removable media.";
			break;
		case DRIVE_FIXED:
			v = "The drive has fixed media.";
			break;
		case DRIVE_REMOTE:
			v = "The drive is a remote (network) drive.";
			break;
		case DRIVE_CDROM:
			v = "The drive is a CD-ROM drive.";
			break;
		case DRIVE_RAMDISK:
			v = "The drive is a RAM disk";
			break;
		default:;
		}
		return v;
	}

	string DISKS::getLogicaDiskFaileSystem(string _drive) {

		string v;
		const char* drive = _drive.c_str();
		char buffer[256];

		DWORD sizebuf = 256;

		if (GetVolumeInformationA(drive, NULL, NULL, NULL, NULL, NULL, buffer, sizebuf)) {

			v = buffer;

		} else {

			cout << typeid(DISKS).name() << ". Error getting information. " << GetLastError() << endl;

		}

		return v;
	}

