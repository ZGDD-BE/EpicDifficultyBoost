#include <global.h>

namespace FishingMonster
{
    bool triggerEvent()
    {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::uniform_real_distribution<float> distribution(0.0, 1.0);
        float randomPercentage = distribution(generator);
        return randomPercentage <= settings::FishingMonsterPersentage;
    }
    Actor *genRandomMonster(Actor *actor)
    {
        Vec3 pos(actor->getPos());
        int dimid = static_cast<int>(actor->getDimensionId());
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 gen(seed);
        std::discrete_distribution<> dist(settings::FishingMonsterchances.begin(), settings::FishingMonsterchances.end());
        int index = dist(gen);
        std::string monsterName = settings::FishingMonsterTypeList[index].at("type").get<std::string>();
        return Global<Level>->getSpawner().spawnMob(pos, dimid, monsterName);
    }

    Actor *replaceMonstor(Actor *actor)
    {
        Actor *monster = genRandomMonster(actor);
        actor->remove();
        return monster;
    }
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    FishingHookMob,
    FishingHook,
    HookPriority::Normal,
    "?_pullCloser@FishingHook@@IEAAXAEAVActor@@M@Z",
    void,
    Actor *actor, float a2)
{
    if (this->getOwner()->isPlayer() && actor->isItemActor() && settings::FishingMonster)
    {
        if (FishingMonster::triggerEvent())
        {
            try
            {
                return origin(FishingMonster::replaceMonstor(actor), a2);
            }
            catch (...)
            {
                return origin(actor, a2);
            }
        }
    }
    return origin(actor, a2);
}