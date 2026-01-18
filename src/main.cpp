#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(MyBot, PlayLayer) {
    void update(float dt) {
        PlayLayer::update(dt);
        auto player = this->m_player1;
        if (!player || player->m_isDead) return;

        float pX = player->getPositionX();
        float pY = player->getPositionY();

        CCObject* obj;
        CCARRAY_FOREACH(this->m_objects, obj) {
            auto gameObj = typeinfo_cast<GameObject*>(obj);
            if (!gameObj) continue;

            if (gameObj->m_objectType == GameObjectType::Hazard) {
                float dist = gameObj->getPositionX() - pX;
                if (dist > 0 && dist < 60 && std::abs(gameObj->getPositionY() - pY) < 30) {
                    player->pushButton(PlayerButton::Jump);
                    break;
                }
            }
        }
    }
};
