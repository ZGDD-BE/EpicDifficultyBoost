#include <global.h>
#include <llapi/mc/Attribute.hpp>
#include <llapi/mc/AttributeInstance.hpp>

namespace HardCorePlayer {
    void hungerTick(Player* player){
        if (!player->isHungry()){
            const_cast<AttributeInstance&>(player->getAttribute(Player::HUNGER)).setMaxValue(21.0f);
            const_cast<AttributeInstance&>(player->getAttribute(Player::HUNGER)).setCurrentValue(20.0f);
        }
    }
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    HungerTick,
    PlayerEventCoordinator,
    HookPriority::Normal,
    "?sendPlayerTick@PlayerEventCoordinator@@QEAAXAEAVPlayer@@@Z",
    void,
    Player* player
) {
    if (settings::HardCorePlayer) {
        try {
            HardCorePlayer::hungerTick(player);
        }
        catch (...) {
            return origin(player);
        }
    }
    return origin(player);
}
