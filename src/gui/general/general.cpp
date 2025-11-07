#include "gui/general/general.hpp"
#include <gui/gui.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>
#include <settings/settings.hpp>

namespace gui {
    void general_t::render() {
        ImGui::SetNextWindowPos(ImVec2(0, 15.f), ImGuiCond_FirstUseEver);

        if (ImGui::Begin("General", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize))
            ImGui::InputText("Search feature", &search_query);

        ImGui::End();

        ImGui::SameLine();
    }
} // namespace gui