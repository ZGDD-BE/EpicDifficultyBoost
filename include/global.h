#pragma once

#include "llapi/LoggerAPI.h"

extern Logger logger;
inline bool isInit = false;
//LLAPI
#include <llapi/Global.h>
#include <llapi/ScheduleAPI.h>
#include <llapi/RegCommandAPI.h>
#include <llapi/DynamicCommandAPI.h>
#include <llapi/EventAPI.h>

//EDB
#include <settings.h>
#include <memory/hook.h>

//thrid-party
#include <SQLiteCpp/SQLiteCpp.h>

//MCAPI
#include <llapi/mc/PlayerInventory.hpp>
#include <llapi/mc/Inventory.hpp>
#include <llapi/mc/ActorDamageSource.hpp>
#include <llapi/mc/AttributeInstance.hpp>
#include <llapi/mc/CompoundTag.hpp>
#include <llapi/mc/Attribute.hpp>
#include <llapi/mc/PacketSender.hpp>
#include <llapi/mc/Certificate.hpp>
#include <llapi/mc/RangedAttackGoal.hpp>
#include <llapi/mc/ShooterComponent.hpp>
#include <llapi/mc/ActorDefinitionIdentifier.hpp>
#include <llapi/mc/ItemActor.hpp>
#include <llapi/mc/CompoundTag.hpp>
#include <llapi/mc/Spawner.hpp>
#include <llapi/mc/Attribute.hpp>
#include <llapi/mc/AttributeInstance.hpp>
#include <llapi/mc/BaseAttributeMap.hpp>
#include <llapi/mc/PlayerEventCoordinator.hpp>
#include <llapi/mc/VariantParameterList.hpp>
#include <llapi/mc/Creeper.hpp>
#include <llapi/mc/Actor.hpp>
#include <llapi/mc/FishingHook.hpp>
#include <llapi/mc/HashedString.hpp>
#include <llapi/mc/ServerPlayer.hpp>
#include <llapi/mc/Randomize.hpp>
#include <llapi/mc/CropBlock.hpp>
#include <llapi/mc/Block.hpp>
#include <llapi/mc/BlockLegacy.hpp>
#include <llapi/mc/BlockInstance.hpp>
#include <llapi/mc/NetherWartBlock.hpp>
#include <llapi/mc/EnchantUtils.hpp>
#include <llapi/mc/Random.hpp>
#include <llapi/mc/ItemStack.hpp>
#include <llapi/mc/Item.hpp>
#include <llapi/mc/Level.hpp>
#include <llapi/mc/VanillaItemNames.hpp>
#include <llapi/mc/ItemInstance.hpp>
#include <llapi/mc/GameMode.hpp>
#include <llapi/mc/Vec3.hpp>
#include <llapi/mc/BlockPos.hpp>
#include <llapi/mc/mce.hpp>
#include <llapi/mc/Vec2.hpp>
#include <llapi/mc/Vec2.hpp>