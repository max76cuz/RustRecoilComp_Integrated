#include <Windows.h>
#include <thread>
#include "DriverComm.h"
#include "RecoilManager.h"
#include "ConfigManager.h"
#include "WeaponDetection.h"
#include "imgui.h"

bool recoilEnabled = true;

void ProcessHotkeys() {
    if (GetAsyncKeyState(VK_F1) & 1) {
        recoilEnabled = !recoilEnabled;
    }
}

int main() {
    DriverComm::Init();
    ConfigManager::LoadConfig("recoil_config.json");

    // Initialize ImGui window here (setup ImGui context, window, etc.)

    while (true) {
        ProcessHotkeys();

        int weaponId = DriverComm::ReadWeaponId();
        std::string weaponName = WeaponDetection::GetWeaponName(weaponId);

        if (recoilEnabled && weaponName != "Unknown") {
            RecoilManager::ApplyRecoil(weaponName);
        }

        // ImGui rendering
        ImGui::Begin("Rust Recoil Compensation");
        ImGui::Text("Weapon: %s", weaponName.c_str());
        ImGui::Text("Recoil: %s (F1)", recoilEnabled ? "ON" : "OFF");
        if (ImGui::Button("Save Config")) {
            ConfigManager::SaveConfig("recoil_config.json");
        }
        if (ImGui::Button("Load Config")) {
            ConfigManager::LoadConfig("recoil_config.json");
        }
        ImGui::End();

        // (Your ImGui render present code here...)

        std::this_thread::sleep_for(std::chrono::milliseconds(5)); // Small frame delay
    }

    return 0;
}
