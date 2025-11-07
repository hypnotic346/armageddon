#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

#include <settings/settings.hpp>

using namespace geode::prelude;

namespace hacks {
    //TODO: add accuracy, death limit.
    class $modify(play_layer, PlayLayer) {
        void destroyPlayer(PlayerObject *p0, GameObject *p1) {
            if (settings::get<bool>("universal.noclip")) return;
        
            PlayLayer::destroyPlayer(p0, p1);
        }   
    };
}