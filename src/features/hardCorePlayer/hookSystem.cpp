#include <global.h>
#include "hardCorePlayer.h"

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

LL_AUTO_TYPED_INSTANCE_HOOK(
    PlayerEat,
    Player,
    HookPriority::Normal,
    "?eat@Player@@QEAAXAEBVItemStack@@@Z",
    void,
    ItemStack* item) {
    if (settings::HardCorePlayer && settings::FoodEnhance) {
        try {
            HardCorePlayer::eatFood(this,item);
        }
        catch (...) {
            return origin(item);
        }
    }
    return origin(item);
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    healthTick,
    Player,
    HookPriority::Normal,
    "?normalTick@Player@@UEAAXXZ",
    void) {
    if (settings::HardCorePlayer && settings::NormalHealth) {
        try {
            HardCorePlayer::healthTick(this);
		}
        catch (...) {
			return origin();
		}
	}
	return origin();
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    defaultHealth,
    ServerPlayer,
    HookPriority::Highest,
    "?setLocalPlayerAsInitialized@ServerPlayer@@QEAAXXZ",
    bool) {
    if (settings::HardCorePlayer && settings::NormalHealth) {
        try {
            HardCorePlayer::loadDefaultHealth(this);
            origin();
        }
        catch (...) {
            return origin();
        }
    }
    return origin();
}

//LL_AUTO_TYPED_INSTANCE_HOOK(
//    defaultHealth_,
//    Player,
//    HookPriority::Normal,
//    "?readAdditionalSaveData@Player@@MEAAXAEBVCompoundTag@@AEAVDataLoadHelper@@@Z",
//    void,
//    CompoundTag* a2, 
//    DataLoadHelper* a3) {
//    if (settings::HardCorePlayer && settings::NormalHealth) {
//        try {
//            HardCorePlayer::loadDefaultHealth(this);
//            origin(a2, a3);
//        }
//        catch (...) {
//            origin(a2, a3);
//        }
//    }
//    origin(a2, a3);
//}


