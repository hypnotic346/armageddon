#include "hitboxes.hpp"
#include "Geode/cocos/draw_nodes/CCDrawNode.h"
#include <geode/modify/GJBaseGameLayer.hpp>
#include <geode/modify/GameObject.hpp>

#include <settings/settings.hpp>

namespace hacks {
    bool active1 = false, active2 = false;

    class $modify(game_object, GameObject) {
        void update(float p0) {
            GameObject::update(p0);

            const PlayLayer *play_layer = PlayLayer::get();

            if (!play_layer) return;

            CCDrawNode *node = play_layer->m_debugDrawNode;

            const GameObjectType object_type = this->m_objectType;
            const CCRect rect = this->getObjectRect();

            const float hitbox_scale = this->getScale();
            const float radius = this->getObjectRadius();

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

                    node->drawPolygon(rect_vertices.data(), rect_vertices.size(), {}, 0.5f, col);
                } break;
                default:
                    break;
            }
        }
    };

    class $modify(base_game_layer, GJBaseGameLayer) {
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

                        node->drawPolygon(rotated_vertices.data(), rotated_vertices.size(), {}, 0.5f, ccColor4F(0.55f, 0.0f, 0.0f, 1.0f));
                        node->drawPolygon(vertices.data(), vertices.size(), {}, 0.5f, ccColor4F(1.0f, 0.0f, 0.0f, 1.0f));
                    }
                }
            }
        }
    };
} // namespace hacks