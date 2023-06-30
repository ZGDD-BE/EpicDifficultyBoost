#include <global.h>

namespace SuperSkeleton{
    void shootGoal(RangedAttackGoal* RAG) {
        //*((Actor**)this + 7) Actor ptr
        //*((unsigned int*)this + 27) cooldown

        auto ac = *((Actor**)RAG + 7);
        if (ac->hasFamily(HashedString("skeleton")) && *((unsigned int*)RAG + 27) > settings::SuperSkeletonSpeedLimit)
        {
            *((unsigned int*)RAG + 27) = settings::SuperSkeletonSpeedLimit;
        }
    }
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    RangedAttackGoalHks,
    RangedAttackGoal,
    HookPriority::Normal,
    "?handleAttackBehavior@RangedAttackGoal@@QEAAXPEAVActor@@AEBVVec3@@M_N@Z",
    void,
    struct Actor* lockedTarget,
    const struct Vec3* a3,
    float a4,
    bool a5) {
    if (settings::SuperSkeleton) {
        try {
            SuperSkeleton::shootGoal(this);
        }
        catch (...) {
            return origin(lockedTarget, a3, a4, a5);
        }
    }
    return origin(lockedTarget, a3, a4, a5);
}