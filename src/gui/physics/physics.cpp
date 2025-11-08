#include "physics.hpp"
#include <gui/gui.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>
#include <settings/settings.hpp>

namespace gui {
    void physics_t::render() {
        ImGui::SetNextWindowPos(ImGui::GetWindowPos(), ImGuiCond_FirstUseEver);

        if (ImGui::Begin("Game", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize)) {
            add_checkbox("Unlock FPS", &settings::get<bool>("physics.unlock_fps"));
            add_slider_int("FPS Amount", &settings::get<int>("physics.fps_amt"), 5.0f, 1000.0f, "%d FPS");

            if (ImGui::Button("Apply FPS")) {
                const auto game = GameManager::get();

                game->m_customFPSTarget = settings::get<int>("physics.fps_amt");
                game->updateCustomFPS();
            }
        }

        ImGui::End();

        ImGui::SameLine();
    }
} // namespace gui