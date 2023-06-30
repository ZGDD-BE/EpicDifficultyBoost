#include <global.h>
#include <llapi/mc/GameRules.hpp>
namespace WorldSettings {
    void gameRules() {
        Global<Level>->executeCommandEx(fmt::format("daylock {}", settings::AlwaysNight).c_str());
        if (settings::AlwaysNight) { Global<Level>->executeCommandEx("time set midnight"); }
        Global<Level>->executeCommandEx(fmt::format("gamerule naturalRegeneration {}", settings::NaturalRegeneration).c_str());

    }
}

#include <llapi/mc/ServerInstance.hpp>
LL_AUTO_TYPED_INSTANCE_HOOK(
    WorldSStart,
    ServerInstance,
    HookPriority::Normal,
    "?sendServerThreadStarted@ServerInstanceEventCoordinator@@QEAAXAEAVServerInstance@@@Z",
    void) {
    origin();
    WorldSettings::gameRules();
}