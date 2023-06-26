#pragma once

#include <Nlohmann/json.hpp>

namespace settings {
    extern bool SuperCreeper;
    extern bool HardCorePlayer;
    nlohmann::json globaljson();
    void initjson(nlohmann::json json);
    void writeDefaultConfig(const std::string& fileName);
    void loadConfigFromJson(const std::string& fileName);
    void reloadJson(const std::string& fileName);
} // namespace settings