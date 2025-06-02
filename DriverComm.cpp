#include "DriverComm.h"
#include <iostream>

HANDLE DriverComm::driverHandle = INVALID_HANDLE_VALUE;

bool DriverComm::Init() {
    driverHandle = CreateFileA("\\\\.\\MyDriverLink",  // Driver link name
                               GENERIC_READ | GENERIC_WRITE,
                               0, nullptr,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL,
                               nullptr);

    if (driverHandle == INVALID_HANDLE_VALUE) {
        std::cerr << "[-] Failed to open driver: " << GetLastError() << std::endl;
        return false;
    }
    std::cout << "[+] Driver opened successfully." << std::endl;
    return true;
}

void DriverComm::Close() {
    if (driverHandle != INVALID_HANDLE_VALUE) {
        CloseHandle(driverHandle);
        driverHandle = INVALID_HANDLE_VALUE;
    }
}

// Example IOCTL code definitions (replace with your driver’s codes!)
#define IOCTL_READ_WEAPON_ID CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_READ_DATA)
#define IOCTL_SEND_MOUSE_MOVE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_WRITE_DATA)

// Read weapon ID from game
int DriverComm::ReadWeaponId() {
    if (driverHandle == INVALID_HANDLE_VALUE)
        return -1;

    int weaponId = 0;
    DWORD bytesReturned;
    if (!DeviceIoControl(driverHandle, IOCTL_READ_WEAPON_ID, nullptr, 0, &weaponId, sizeof(weaponId), &bytesReturned, nullptr)) {
        std::cerr << "[-] Failed to read weapon ID: " << GetLastError() << std::endl;
        return -1;
    }
    return weaponId;
}

// Send mouse move command to driver
void DriverComm::SendMouseMove(int dx, int dy) {
    if (driverHandle == INVALID_HANDLE_VALUE)
        return;

    struct MouseMove {
        int dx;
        int dy;
    } move = { dx, dy };

    DWORD bytesReturned;
    if (!DeviceIoControl(driverHandle, IOCTL_SEND_MOUSE_MOVE, &move, sizeof(move), nullptr, 0, &bytesReturned, nullptr)) {
        std::cerr << "[-] Failed to send mouse move: " << GetLastError() << std::endl;
    }
}
