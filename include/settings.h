#pragma once

#include <Nlohmann/json.hpp>
#include <utils/SU.hpp>

namespace settings {
    // HardCorePlayer settings
    extern SU<bool> HardCorePlayer;
    extern SU<bool> FoodEnhance;
    extern SU<bool> NormalHealth;
    extern SU<int> NormalHealthPoint;
    extern SU<jsonDictVector> FoodList;
    extern SU<bool> KeepInv;
    extern SU<bool> SleepingHungerToHealth;
    extern SU<std::string> KeepInvCostItem;
    extern std::unordered_map<std::string, int> Foods;

    // FishingMonster settings
    extern SU<bool> FishingMonster;
    extern SU<double> FishingMonsterPersentage;
    extern SU<jsonDictVector> FishingMonsterTypeList;
    extern std::vector<double> FishingMonsterchances;

    // SuperCreeper settings
    extern SU<bool> SuperCreeper;

    // SuperSkeleton settings
    extern SU<bool> SuperSkeleton;
    extern SU<int> SuperSkeletonSpeedLimit;

    // GameRules settings
    extern SU<bool> AlwaysNight;
    extern SU<bool> NaturalRegeneration;

    nlohmann::json globaljson();
    void initjson(nlohmann::json json);
    void writeDefaultConfig(const std::string& fileName);
    void loadConfigFromJson(const std::string& fileName);
    void reloadJson(const std::string& fileName);
} // namespace settings