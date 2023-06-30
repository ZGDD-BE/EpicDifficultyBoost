#pragma once

#include <Nlohmann/json.hpp>
#include <utils/SU.hpp>

namespace settings {
    using jsonDictVector = std::vector<std::unordered_map<std::string, nlohmann::json>>;
    extern std::unordered_map<std::string,int> Foods;
    extern SU<bool> FoodEnhance;
    extern SU<bool> SuperCreeper;
    extern SU<bool> HardCorePlayer;
    extern SU<bool> FishingMonster;
    extern SU<double> FishingMonsterPersentage;
    extern SU<jsonDictVector> FishingMonsterTypeList;
    extern std::vector<double> FishingMonsterchances;
    extern SU<bool> SuperSkeleton;
    extern SU<int> SuperSkeletonSpeedLimit;
    extern SU<bool> NormalHealth;
    extern SU<int> NormalHealthPoint;
    nlohmann::json globaljson();
    void initjson(nlohmann::json json);
    void writeDefaultConfig(const std::string& fileName);
    void loadConfigFromJson(const std::string& fileName);
    void reloadJson(const std::string& fileName);
} // namespace settings