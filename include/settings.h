#pragma once

#include <Nlohmann/json.hpp>
#include <utils/SU.hpp>

namespace settings {
    using jsonDictVector = std::vector<std::unordered_map<std::string, nlohmann::json>>;
    extern SU<bool> SuperCreeper;
    extern SU<bool> HardCorePlayer;
    extern SU<bool> FishingMonster;
    extern SU<double> FishingMonsterPersentage;
    extern SU<jsonDictVector> FishingMonsterTypeList;
    extern std::vector<double> FishingMonsterchances;
    nlohmann::json globaljson();
    void initjson(nlohmann::json json);
    void writeDefaultConfig(const std::string& fileName);
    void loadConfigFromJson(const std::string& fileName);
    void reloadJson(const std::string& fileName);
} // namespace settings