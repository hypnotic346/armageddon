#include "gui/universal/universal.hpp"
#include "gui/general/general.hpp"
#include <gui/gui.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>
#include <settings/settings.hpp>

namespace gui {
    void universal_t::render() {
        ImGui::SetNextWindowPos(ImGui::GetWindowPos(), ImGuiCond_FirstUseEver);

        if (ImGui::Begin("Universal", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize)) {
            add_checkbox("Noclip", &settings::get<bool>("universal.noclip"));
            add_checkbox("Show hitboxes", &settings::get<bool>("universal.show_hitboxes"));
            add_checkbox("Show hitboxes on death", &settings::get<bool>("universal.show_hitboxes_death"));
        }

        ImGui::End();

        ImGui::SameLine();
    }
} // namespace gui