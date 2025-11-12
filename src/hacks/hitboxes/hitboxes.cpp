#include "hitboxes.hpp"
#include "Geode/cocos/draw_nodes/CCDrawNode.h"
#include "ccTypes.h"
#include <geode/modify/GJBaseGameLayer.hpp>
#include <geode/modify/GameObject.hpp>

#include <settings/settings.hpp>

namespace hacks {
    bool active1 = false, active2 = false;

    namespace util {
        // thx prevter (https://github.com/EclipseMenu/EclipseMenu/blob/c3f7239decca141d8c8c2d3bdc917ace4f23ecbf/src/hacks/Level/ShowHitboxes.cpp#L131-L234)
        static void for_each_object(const GJBaseGameLayer *game, const std::function<void(GameObject *)> &callback) {
            const int count = game->m_sections.empty() ? -1 : game->m_sections.size();

            for (int i = game->m_leftSectionIndex; i <= game->m_rightSectionIndex && i < count; ++i) {
                const auto left_section = game->m_sections[i];

                if (!left_section) continue;

                const auto left_section_size = left_section->size();

                for (int j = game->m_bottomSectionIndex; j <= game->m_topSectionIndex && j < left_section_size; ++j) {
                    auto section = left_section->at(j);
                    if (!section) continue;

                    const auto section_size = game->m_sectionSizes[i]->at(j);

                    for (int k = 0; k < section_size; ++k) {
                        auto obj = section->at(k);
                        if (!obj) continue;

                        callback(obj);
                    }
                }
            }
        }
    } // namespace util

    class $modify(base_game_layer, GJBaseGameLayer) {
        float getModifiedDelta(float p0) {
            float m_resumeTimer; // x0
            double m_extraDelta; // d1
            float m_timeWarp;    // s2
            float v6;            // s1
            double v7;           // d2
            double v8;           // d1
            float v9;            // s0
            double v10;          // d0
            double v11;          // d1
            float result;        // s0

            m_resumeTimer = this->m_resumeTimer;
            if (m_resumeTimer <= 0) {
                m_timeWarp = this->m_gameState.m_timeWarp;
                v6 = p0 + this->m_extraDelta;
                if (m_timeWarp >= 1.0)
                    goto LABEL_3;
            LABEL_6:
                v7 = (float) (m_timeWarp * 0.0041667);
                goto LABEL_4;
            }
            //cocos2d::CCDirector::sharedDirector(m_resumeTimer);
            m_extraDelta = this->m_extraDelta;
            m_timeWarp = this->m_gameState.m_timeWarp;
            --this->m_resumeTimer;
            v6 = m_extraDelta + 0.0;
            if (m_timeWarp < 1.0)
                goto LABEL_6;
        LABEL_3:
            v7 = 0.00416666688f;
        LABEL_4:
            v8 = v6;
            v9 = v8 / v7;
            v10 = v7 * (double) (int) llroundf(v9);
            v11 = v8 - v10;
            result = v10;
            this->m_extraDelta = v11;
            return result;
        }

        // (@hypnotic) summary: draws hitboxes on player (+ on death)
        void update(float dt) {
            const auto rotate = [](CCPoint p, const CCPoint &pivot, const float angle) -> CCPoint {
                return p.rotateByAngle(pivot, -CC_DEGREES_TO_RADIANS(angle));
            };

            GJBaseGameLayer::update(dt);

            player1_ = this->m_player1;
            player2_ = this->m_player2;

            active1 = settings::get<bool>("universal.show_hitboxes");
            active2 = settings::get<bool>("universal.show_hitboxes_death");

            CCDrawNode *node = this->m_debugDrawNode;

            const bool should_update = active1 || active2;

            node->setVisible(should_update);

            if (should_update) {
                node->clear();

                if (player1_ != nullptr) {
                    const CCRect rect = player1_->getObjectRect();

                    if (active1 || (active2 && player1_->m_isDead)) {
                        const CCPoint origin = player1_->getPosition();
                        const float rotation = player1_->getRotation();

                        std::array<CCPoint, 4> vertices = {
                            CCPointMake(rect.getMinX(), rect.getMinY()),
                            CCPointMake(rect.getMinX(), rect.getMaxY()),
                            CCPointMake(rect.getMaxX(), rect.getMaxY()),
                            CCPointMake(rect.getMaxX(), rect.getMinY())};

                        std::array<CCPoint, 4> rotated_vertices = {
                            rotate(CCPointMake(rect.getMinX(), rect.getMinY()), origin, rotation),
                            rotate(CCPointMake(rect.getMinX(), rect.getMaxY()), origin, rotation),
                            rotate(CCPointMake(rect.getMaxX(), rect.getMaxY()), origin, rotation),
                            rotate(CCPointMake(rect.getMaxX(), rect.getMinY()), origin, rotation)};

                        /* player hitboxes */ {
                            node->drawPolygon(rotated_vertices.data(), rotated_vertices.size(), {}, 0.5f, ccColor4F(0.55f, 0.0f, 0.0f, 1.0f));
                            node->drawPolygon(vertices.data(), vertices.size(), {}, 0.5f, ccColor4F(1.0f, 0.0f, 0.0f, 1.0f));
                        }

                        /* object hitboxes */ {
                            util::for_each_object(this, [&](GameObject *object) {
                                const GameObjectType object_type = object->m_objectType;
                                const CCRect rect = object->getObjectRect();

                                const CCPoint origin = object->getPosition();
                                const float hitbox_scale = object->getScale();
                                const float radius = object->getObjectRadius();

                                ccColor4F col = {};

                                std::array<CCPoint, 4> rect_vertices = {
                                    CCPointMake(rect.getMinX(), rect.getMinY()) * hitbox_scale,
                                    CCPointMake(rect.getMinX(), rect.getMaxY()) * hitbox_scale,
                                    CCPointMake(rect.getMaxX(), rect.getMaxY()) * hitbox_scale,
                                    CCPointMake(rect.getMaxX(), rect.getMinY()) * hitbox_scale};

                                switch (object_type) {
                                    case GameObjectType::Hazard:
                                    case GameObjectType::Breakable:
                                    case GameObjectType::Solid: {
                                        col = {0.0f, 0.0f, 1.0f, 1.0f};

                                        if (object_type == GameObjectType::Hazard)
                                            col = {1.0f, 0.0f, 0.0f, 1.0f};

                                        if (object->m_objectRadius > 0.f) {
                                            node->drawCircle(origin, radius, {}, 0.5f, col, 24); // segments = 8 * 3 (ngl its too jagged with 8 segs)
                                        } else {
                                            node->drawPolygon(rect_vertices.data(), rect_vertices.size(), {}, 0.5f, col);
                                        }
                                    } break;
                                    default:
                                        break;
                                }
                            });
                        }
                    }
                }
            }
        }
    };
} // namespace hacks