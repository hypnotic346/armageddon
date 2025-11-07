#include "imgui/imgui.h"
#include <Geode/Geode.hpp>
#include <gui/gui.hpp>

using namespace geode::prelude;

#ifdef GEODE_IS_WINDOWS
#define strcpy strcpy_s
#endif

$on_mod(Loaded) {
    gui::ctx->setup();
    gui::ctx->render();
}

#ifndef GEODE_IS_IOS
#include <Geode/modify/CCKeyboardDispatcher.hpp>
class $modify(ImGuiKeybindHook, cocos2d::CCKeyboardDispatcher) {
    bool dispatchKeyboardMSG(cocos2d::enumKeyCodes key, bool isKeyDown, bool isKeyRepeat) {
        if (key == cocos2d::enumKeyCodes::KEY_Tab && isKeyDown) {
            ImGuiCocos::get().toggle();
        }
        return CCKeyboardDispatcher::dispatchKeyboardMSG(key, isKeyDown, isKeyRepeat);
    }
};
#endif