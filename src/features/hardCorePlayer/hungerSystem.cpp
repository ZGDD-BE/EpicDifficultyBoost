#include <global.h>
#include <llapi/mc/Attribute.hpp>
#include <llapi/mc/AttributeInstance.hpp>

namespace HardCorePlayer {
    void hungerTick(Player* player) {
        if (!player->isHungry()) {
            const_cast<AttributeInstance&>(player->getAttribute(Player::HUNGER)).setMaxValue(21.0f);
            const_cast<AttributeInstance&>(player->getAttribute(Player::HUNGER)).setCurrentValue(20.0f);
        }
    }
}