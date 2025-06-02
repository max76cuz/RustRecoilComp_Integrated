#include <Windows.h>
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
    // Initialize ImGui, Window, etc.
    // (Boilerplate ImGui DX11/GLFW initialization here)

    ConfigManager::LoadConfig("recoil_config.json");

    while (true) {
        ProcessHotkeys();

        // Read active weapon from game memory via DriverComm
        int weaponId = DriverComm::ReadWeaponId();

        std::string weaponName = WeaponDetection::GetWeaponName(weaponId);

        if (recoilEnabled) {
            RecoilManager::ApplyRecoil(weaponName);
        }

        // ImGui rendering
        ImGui::Begin("RustRecoilComp");
        ImGui::Text("Recoil: %s (F1)", recoilEnabled ? "ON" : "OFF");
        if (ImGui::Button("Save Config")) {
            ConfigManager::SaveConfig("recoil_config.json");
        }
        if (ImGui::Button("Load Config")) {
            ConfigManager::LoadConfig("recoil_config.json");
        }
        ImGui::End();

        // (Render ImGui)
    }

    return 0;
}
