#include <global.h>

namespace SuperCreeper {
    auto halfMaxHealth = 10;

    bool isIgnited(Actor* _this, bool flag) {
        if (flag) {
            _this->addTag("wannaExplode");
        } else {
            _this->removeTag("wannaExplode");
        }
        return false;
    }

    void normalTick(Creeper* _this) {
        auto tags = _this->getTags();
        if (std::find(tags.begin(), tags.end(), "wannaExplode") != tags.end()) {
            MobEffectInstance effect(MobEffect::MOVEMENT_SPEED->getId(), 100, 5, false, false,false);
            _this->addEffect(effect);
        }
    }

    bool hurt(Mob* _this, float damage, ActorDamageSource* src){
    if(src->getCause() == ActorDamageCause::EntityExplosion){
        //logger.info("Creeper hurt by explosion");
        return false;
    }
    if (_this->getHealth()-damage <= halfMaxHealth){
        auto tags = _this->getTags();
        if ((std::find(tags.begin(), tags.end(), "F") == tags.end())){
            _this->executeEvent("minecraft:start_exploding_forced",VariantParameterList());
            _this->addTag("F");
            }
        //logger.info("Creeper health is less than half");
        }
    //logger.info("Creeper_hurt");
    return true;
    }
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    ActorIsIgnited,
    Actor,
    HookPriority::Normal,
    "?isIgnited@Actor@@QEBA_NXZ",
    bool
) {
    if (settings::SuperCreeper && this->getTypeName() == "minecraft:creeper") {
        try {
            return SuperCreeper::isIgnited(this,origin());
        }
        catch (...) {
            return origin();
        }
    }
    return origin();
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    CreeperNormalTick,
    Creeper,
    HookPriority::Normal,
    "?normalTick@Creeper@@UEAAXXZ",
    void
) {
    if (settings::SuperCreeper) {
        try {
            SuperCreeper::normalTick(this);
        }
        catch (...) {
            return origin();
        }
    }
    return origin();
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    CreeperMobHurt_,
    Mob,
    HookPriority::Normal,
    "?_hurt@Mob@@MEAA_NAEBVActorDamageSource@@M_N1@Z",
    bool,
    ActorDamageSource& src, float damage,bool unk1_1, bool unk2_0
){
    if (settings::SuperCreeper && this->getTypeName() == "minecraft:creeper") {
        try {
            if (SuperCreeper::hurt(this,damage,&src))
                return origin(src,damage,unk1_1,unk2_0);
        }
        catch (...) {
            return origin(src,damage,unk1_1,unk2_0);
        }
    }
    return origin(src,damage,unk1_1,unk2_0);
}

LL_AUTO_TYPED_INSTANCE_HOOK(
    CreeperMobHurt,
    Mob,
    HookPriority::Normal,
    "?getDamageAfterResistanceEffect@Mob@@UEBAMAEBVActorDamageSource@@M@Z",
    float,
    ActorDamageSource* src, float damage
){
    if(this && settings::SuperCreeper){
        if (src->getCause() == ActorDamageCause::Magic && this->getTypeName() == "minecraft:creeper") {
            try {
                if (SuperCreeper::hurt(this,damage,src))
                    return origin(src,damage);
            }
            catch (...) {
                return origin(src,damage);
                }
        }
    }
    return origin(src,damage);    
}