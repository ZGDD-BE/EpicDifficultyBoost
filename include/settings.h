#pragma once

#include <Nlohmann/json.hpp>

namespace settings {
    using jsonDictVector = std::vector<std::unordered_map<std::string, nlohmann::json>>;
    extern bool SuperCreeper;
    extern bool HardCorePlayer;
    extern bool FishingMonster;
    extern double FishingMonsterPersentage;
    extern jsonDictVector FishingMonsterTypeList;
    extern std::vector<double> FishingMonsterchances;
    nlohmann::json globaljson();
    void initjson(nlohmann::json json);
    void writeDefaultConfig(const std::string& fileName);
    void loadConfigFromJson(const std::string& fileName);
    void reloadJson(const std::string& fileName);
} // namespace settings