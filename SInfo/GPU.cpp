#include "GPU.h"



std::string GPU::getGPUName_Win32() {
    DISPLAY_DEVICEA dd;
    dd.cb = sizeof(DISPLAY_DEVICEA);
    EnumDisplayDevicesA(NULL, 0, &dd, EDD_GET_DEVICE_INTERFACE_NAME);
    return std::string(dd.DeviceString);
}
