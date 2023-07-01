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

    void hungerToHealth(Player* player) {
        auto health = const_cast<AttributeInstance&>(player->getAttribute(Attribute::getByName("minecraft:health"))).getCurrentValue();
        auto maxhealth = const_cast<AttributeInstance&>(player->getAttribute(Attribute::getByName("minecraft:health"))).getMaxValue();
        auto hunger = const_cast<AttributeInstance&>(player->getAttribute(Player::HUNGER)).getCurrentValue();
        //logger.info("{} {} {} {}", health, maxhealth, hunger, health < maxhealth);
        if (health < maxhealth && hunger > 3) {
            player->heal(1);
            const_cast<AttributeInstance&>(player->getAttribute(Player::HUNGER)).setCurrentValue(hunger - 2);
        }
    }
}