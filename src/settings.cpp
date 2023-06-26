#include <global.h>
#include <settings.h>
#include <Nlohmann/json.hpp>
#include <llapi/utils/FileHelper.h>

#define TRJ(key1,key2,val)                                \
if (json.find(key1) != json.end()) {                      \
    if (json.at(key1).find(key2) != json.at(key1).end()) {\
    const nlohmann::json& out2 = json.at(key1).at(key2);  \
         out2.get_to(val);}}                              \


namespace settings {

    bool SuperCreeper = true;
    bool HardCorePlayer = true;
    nlohmann::json globaljson() {
        nlohmann::json json;
        json["SuperCreeper"]["Enabled"] = SuperCreeper;
        json["HardCorePlayer"]["Enabled"] = HardCorePlayer;
        return json;
    }

    void initjson(nlohmann::json json) {
        TRJ("SuperCreeper","Enabled", SuperCreeper);
        TRJ("HardCorePlayer","Enabled", HardCorePlayer);
    }

    void writeDefaultConfig(const std::string& fileName) {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            logger.error("Can't open file {}", fileName);
            return;
        }
        auto json = globaljson();
        file << json.dump(4);
        file.close();
    }

    void loadConfigFromJson(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            logger.error("Can't open file {}", fileName);
            return;
        }
        nlohmann::json json;
        file >> json;
        file.close();
        initjson(json);
        writeDefaultConfig(fileName);
    }
    void reloadJson(const std::string& fileName) {
        std::ofstream file(fileName);
        if (file)
        {
            file << globaljson().dump(4);
        }
        else
        {
            logger.error("Configuration File Creation failed!");
        }
        file.close();
    }
} // namespace settings