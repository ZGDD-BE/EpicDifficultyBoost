#include <global.h>
#include "hardCorePlayer.hpp"

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