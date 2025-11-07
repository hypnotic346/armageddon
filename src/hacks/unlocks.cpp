#include <Geode/Geode.hpp>
#include <Geode/modify/GameManager.hpp>

#include <settings/settings.hpp>

using namespace geode::prelude;

namespace hacks {
    class $modify(game_manager, GameManager) {
        bool isIconUnlocked(int p0, IconType p1)  {
            return settings::get<bool>("cosmetics.unlock") ? true : GameManager::isIconUnlocked(p0, p1);
        }   
    };
}