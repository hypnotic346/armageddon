#include <Geode/Geode.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <settings/settings.hpp>

using namespace geode::prelude;

namespace hacks {
    class $modify(base_game_layer, GJBaseGameLayer) {
    public:
        // float getModifiedDelta(float p0) {
        //     float m_resumeTimer; // x0
        //     double m_extraDelta; // d1
        //     float m_timeWarp;    // s2
        //     float v6;            // s1
        //     double v7;           // d2
        //     double v8;           // d1
        //     float v9;            // s0
        //     double v10;          // d0
        //     double v11;          // d1
        //     float result;        // s0

        //     m_resumeTimer = this->m_resumeTimer;
        //     if (m_resumeTimer <= 0) {
        //         m_timeWarp = this->m_gameState.m_timeWarp;
        //         v6 = p0 + this->m_extraDelta;
        //         if (m_timeWarp >= 1.0)
        //             goto LABEL_3;
        //     LABEL_6:
        //         v7 = (float) (m_timeWarp * 0.0041667);
        //         goto LABEL_4;
        //     }
        //     //cocos2d::CCDirector::sharedDirector(m_resumeTimer);
        //     m_extraDelta = this->m_extraDelta;
        //     m_timeWarp = this->m_gameState.m_timeWarp;
        //     --this->m_resumeTimer;
        //     v6 = m_extraDelta + 0.0;
        //     if (m_timeWarp < 1.0)
        //         goto LABEL_6;
        // LABEL_3:
        //     v7 = 0.00416666688f;
        // LABEL_4:
        //     v8 = v6;
        //     v9 = v8 / v7;
        //     v10 = v7 * (double) (int) llroundf(v9);
        //     v11 = v8 - v10;
        //     result = v10;
        //     this->m_extraDelta = v11;
        //     return result;
        // }
    };
} // namespace hacks