#pragma once

#include <imgui-cocos/imgui-cocos.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

// Tabs
#include <gui/cosmetics/cosmetics.hpp>
#include <gui/general/general.hpp>
#include <gui/universal/universal.hpp>

namespace util {
    inline std::string tolower(std::string text) {
        std::transform(text.begin(), text.end(), text.begin(), ::tolower);
        return text;
    }
} // namespace util

inline std::vector<std::string> _search_items = {};

namespace gui {
    inline std::string search_query = {};

#pragma region controls
    inline void add_checkbox(const char *label, bool *v) {
        bool searching = false, has_field_input = false;

        const auto highlight_control = [](const std::string &query) {
            const auto query_txt = util::tolower(query);
            const auto txt = util::tolower(search_query);

            return query_txt.find(txt) != std::string::npos;
        };

        if (search_query.length() > 0) {
            has_field_input = true;

            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));

            if (highlight_control(label)) {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                searching = true;
            }
        }

        ImGui::Checkbox(label, v);

        if (has_field_input) {
            ImGui::PopStyleColor();

            if (searching)
                ImGui::PopStyleColor();
        }
    }

#pragma endregion controls

    struct context_t {
    public:
        inline void setup() {
            ImGuiCocos::get().setup([] {
                ImGui::StyleColorsDark();

                const auto &io = ImGui::GetIO();

                io.Fonts->AddFontDefault();
            });
        }

        inline void render() {
            ImGuiCocos::get().draw([&] {
                cosmetics->render();
                universal->render();
                general->render();
            });
        }

    protected:
        bool opened_ = true;
    };

    inline context_t *ctx = new context_t;
} // namespace gui