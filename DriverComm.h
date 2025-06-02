#pragma once
#include <Windows.h>

class DriverComm {
public:
    static HANDLE driverHandle;
    static void Init();
    static int ReadWeaponId();
    static void SendMouseMove(int x, int y);

private:
    static void EncryptData(uint8_t* data, size_t size, uint8_t key);
};

// DriverComm.cpp
#include "DriverComm.h"

HANDLE DriverComm::driverHandle;

void DriverComm::Init() {
    driverHandle = CreateFileW(L"\\\\.\\MyDriver", GENERIC_READ | GENERIC_WRITE,
                               0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
}

int DriverComm::ReadWeaponId() {
    int weaponId = 0;
    DWORD bytesReturned;

    uint8_t buffer[sizeof(int)] = {0};
    // XOR encrypt
    EncryptData(buffer, sizeof(int), 0xAA);

    DeviceIoControl(driverHandle, 0x222004, buffer, sizeof(int), buffer, sizeof(int), &bytesReturned, nullptr);

    // XOR decrypt
    EncryptData(buffer, sizeof(int), 0xAA);
    memcpy(&weaponId, buffer, sizeof(int));
    return weaponId;
}

void DriverComm::SendMouseMove(int x, int y) {
    struct {
        int dx;
        int dy;
    } data = {x, y};

    EncryptData(reinterpret_cast<uint8_t*>(&data), sizeof(data), 0xAA);
    DWORD bytesReturned;
    DeviceIoControl(driverHandle, 0x222008, &data, sizeof(data), nullptr, 0, &bytesReturned, nullptr);
}

void DriverComm::EncryptData(uint8_t* data, size_t size, uint8_t key) {
    for (size_t i = 0; i < size; ++i) {
        data[i] ^= key;
    }
}
