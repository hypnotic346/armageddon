#include "gui/cosmetics/cosmetics.hpp"
#include "imgui/imgui.h"

#include <gui/gui.hpp>
#include <settings/settings.hpp>

namespace gui {
    void cosmetics_t::render() {
        ImGui::SetNextWindowPos(ImVec2(10.f, 15.f), ImGuiCond_FirstUseEver);

        if (ImGui::Begin("Cosmetics", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize)) {
            add_checkbox("Unlock icons", &settings::get<bool>("cosmetics.unlock"));
        }
        ImGui::End();

        ImGui::SameLine();
    }
} // namespace gui