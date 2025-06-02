#pragma once
#include <Windows.h>

class DriverComm {
public:
    static bool Init();                    // Open driver handle
    static void Close();                   // Close handle
    static int ReadWeaponId();             // Example: read weapon ID
    static void SendMouseMove(int dx, int dy); // Send recoil move
private:
    static HANDLE driverHandle;            // Global handle
};
