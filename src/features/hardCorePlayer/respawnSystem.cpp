#include <global.h>

nlohmann::json kINv;
nlohmann::json ExpJson;


namespace HardCorePlayer {
    //bool keepInventory(PlayerInventory* _this) {
    //    auto IY = (*((Inventory**)_this + 24));
    //    auto ac = (Actor*)*((unsigned __int64*)IY + 31);
    //    if (ac)
    //    {
    //        auto pl = (Player*)ac;
    //        for (auto item : IY->getAllSlots())
    //        {
    //            if (item->getTypeName() == "minecraft:dirt") {
    //                return true;
    //            }
    //        }
    //    }
    //    return false;
    //}

    bool keepInventory(Player* player) {
        if (player->isPlayer())
        {
            //logger.info("2");
            for (auto item : player->getInventory().getAllSlots()) {
                if (item->getTypeName() == settings::KeepInvCostItem) {
                    ((ItemStackBase*)item)->remove(1);
                    return true;
                }
            }
        }
        return false;
    }

}

#include <llapi/mc/ActorDamageSource.hpp>
#include <llapi/mc/GameRuleId.hpp>
LL_AUTO_TYPED_INSTANCE_HOOK(
    dropAllOnDeath,
    PlayerInventory,
    HookPriority::Normal,
    "?dropAllOnDeath@PlayerInventory@@QEAAX_N@Z",
    void,
    bool onlyClearContainer
) {
    if (settings::HardCorePlayer && !settings::KeepInv) {
        return origin(onlyClearContainer);
    }
    auto ac = (Actor*)*((unsigned __int64*)(*((Inventory**)this + 24)) + 31);
    if (ac && ac->isPlayer())
    {
        auto pl = (Player*)ac;
        if (kINv.contains(pl->getUuid()))
            return;
    }
    origin(onlyClearContainer);
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    dropEquipmentOnDeath,
    Player,
    HookPriority::Normal,
    "?dropEquipmentOnDeath@Player@@UEAAXXZ",
    void
) {
    if (settings::HardCorePlayer && !settings::KeepInv) {
        return origin();
    }
    if (kINv.contains(this->getUuid()))
        return;
    origin();
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    dropEquipmentOnDeath_,
    Player,
    HookPriority::Normal,
    "?dropEquipmentOnDeath@Player@@UEAAXAEBVActorDamageSource@@H@Z",
    void,
    const ActorDamageSource* a2, int a3
) {
    if (settings::HardCorePlayer && !settings::KeepInv) {
        return origin(a2, a3);
    }
    if (kINv.contains(this->getUuid()))
        return;
    origin(a2, a3);
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    clearVanishEnchantedItemsOnDeath,
    ServerPlayer,
    HookPriority::Normal,
    "?clearVanishEnchantedItemsOnDeath@ServerPlayer@@UEAAXXZ",
    void
) {
    if (settings::HardCorePlayer && !settings::KeepInv) {
        return origin();
    }
    if (kINv.contains(this->getUuid()))
        return;
    origin();
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    clearVanishEnchantedItemsOnDeath_,
    PlayerInventory,
    HookPriority::Normal,
    "?clearVanishEnchantedItemsOnDeath@PlayerInventory@@QEAAXXZ",
    void
) {
    if (settings::HardCorePlayer && !settings::KeepInv) {
        return origin();
    }
    auto ac = (Actor*)*((unsigned __int64*)(*((Inventory**)this + 24)) + 31);
    if (ac && ac->isPlayer())
    {
        auto pl = (Player*)ac;
        if (kINv.contains(pl->getUuid()))
            return;
    }
    origin();
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    die,
    ServerPlayer,
    HookPriority::Normal,
    "?die@ServerPlayer@@UEAAXAEBVActorDamageSource@@@Z",
    void,
    const ActorDamageSource* a2
) {
    if (settings::HardCorePlayer && !settings::KeepInv) {
        return origin(a2);
    }
    if (HardCorePlayer::keepInventory(this))
    {
        ExpJson[this->getUuid()] = this->getTotalExperience();
        kINv[this->getUuid()] = true;
        this->setTotalExperience(0);
    }
    origin(a2);
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    respawn,
    Player,
    HookPriority::Normal,
    "?respawn@Player@@UEAAXXZ",
    void
) {
    origin();
    if (settings::HardCorePlayer && !settings::KeepInv) {
        return;
    }
    if (ExpJson.contains(this->getUuid())) {
        auto expe = ExpJson[this->getUuid()].get<int>() + 1;
        ExpJson.erase(this->getUuid());
        kINv.erase(this->getUuid());
        this->setTotalExperience(expe);
    }
}
