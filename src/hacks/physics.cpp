#include <Geode/Geode.hpp>
#include <Geode/modify/CCApplication.hpp>
#include <settings/settings.hpp>

using namespace geode::prelude;

// Physics or FPS bypasses.
namespace hacks {
    class $modify(application, CCApplication) {
        void setAnimationInterval(double interval) {
            double ival = interval;

            if (settings::get<bool>("physics.unlock_fps"))
                ival = 1.0 / static_cast<double>(settings::get<float>("physics.fps_amt"));

            return CCApplication::setAnimationInterval(1.0 / 144);
        }
    };
} // namespace hacks