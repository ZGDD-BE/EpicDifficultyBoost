#include <global.h>
#include <settings.h>
#include <Nlohmann/json.hpp>
#include <llapi/utils/FileHelper.h>

#define TRJ(key1, key2, val)                                     \
    if (json.find(key1) != json.end())                           \
    {                                                            \
        if (json.at(key1).find(key2) != json.at(key1).end())     \
        {                                                        \
            const nlohmann::json &out2 = json.at(key1).at(key2); \
            out2.get_to(val);                                    \
        }                                                        \
    }

#define LTRJ(key1, key2, val)                                         \
    if (json.find(key1) != json.end() &&                              \
        json.at(key1).find(key2) != json.at(key1).end())              \
    {                                                                 \
        const nlohmann::json &out2 = json.at(key1).at(key2);          \
        if (!out2.empty())                                            \
        {                                                             \
            val.clear();                                              \
            for (const auto &item : out2)                             \
            {                                                         \
                std::unordered_map<std::string, nlohmann::json> temp; \
                for (auto &element : item.items())                    \
                {                                                     \
                    temp[element.key()] = element.value();            \
                }                                                     \
                val.push_back(temp);                                  \
            }                                                         \
        }                                                             \
    }

namespace settings
{
    using jsonDictVector = std::vector<std::unordered_map<std::string, nlohmann::json>>;
    bool SuperCreeper = true;
    bool HardCorePlayer = true;
    bool FishingMonster = true;
    double FishingMonsterPersentage = 0.5;
    jsonDictVector FishingMonsterTypeList = {{{"type", "minecraft:zombie"}, {"chance", 1.0}}};
    std::vector<double> FishingMonsterchances;

    template <typename T>
    nlohmann::json loadListJson(const std::vector<T> &list)
    {
        nlohmann::json ListJson;
        for (const auto &item : list)
        {
            nlohmann::json itemJson = item;
            ListJson.push_back(itemJson);
        }
        return ListJson;
    }

    void checkChance()
    {
        double totalChance = 0.0;
        for (const auto &item : FishingMonsterTypeList)
        {
            totalChance += item.at("chance").get<double>();
        }
        if (totalChance != 1.0)
        {
            for (auto &item : FishingMonsterTypeList)
            {
                item["chance"] = item.at("chance").get<double>() / totalChance;
            }
        }
        for (const auto &monsterType : settings::FishingMonsterTypeList)
        {
            FishingMonsterchances.push_back(monsterType.at("chance").get<double>());
        }
    }

    nlohmann::json globalJson()
    {
        nlohmann::json json;
        json["SuperCreeper"]["Enabled"] = SuperCreeper;
        json["HardCorePlayer"]["Enabled"] = HardCorePlayer;
        json["FishingMonster"]["Enabled"] = FishingMonster;
        json["FishingMonster"]["Percentage"] = FishingMonsterPersentage;
        json["FishingMonster"]["FishingMonsterTypeList"] = loadListJson(FishingMonsterTypeList);
        return json;
    }

    void initjson(nlohmann::json json)
    {
        TRJ("SuperCreeper", "Enabled", SuperCreeper);
        TRJ("HardCorePlayer", "Enabled", HardCorePlayer);
        TRJ("FishingMonster", "Enabled", FishingMonster);
        TRJ("FishingMonster", "Percentage", FishingMonsterPersentage);
        LTRJ("FishingMonster", "FishingMonsterTypeList", FishingMonsterTypeList);
        checkChance();
    }

    void writeDefaultConfig(const std::string &fileName)
    {
        std::ofstream file(fileName);
        if (!file.is_open())
        {
            logger.error("Can't open file {}", fileName);
            return;
        }
        auto json = globalJson();
        file << json.dump(4);
        file.close();
    }

    void loadConfigFromJson(const std::string &fileName)
    {
        std::ifstream file(fileName);
        if (!file.is_open())
        {
            logger.error("Can't open file {}", fileName);
            return;
        }
        nlohmann::json json;
        file >> json;
        file.close();
        initjson(json);
        writeDefaultConfig(fileName);
    }
    void reloadJson(const std::string &fileName)
    {
        std::ofstream file(fileName);
        if (file)
        {
            file << globalJson().dump(4);
        }
        else
        {
            logger.error("Configuration File Creation failed!");
        }
        file.close();
    }
} // namespace settings