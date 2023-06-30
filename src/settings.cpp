#include <global.h>
#include <settings.h>
#include <llapi/utils/FileHelper.h>

namespace settings
{
    ///hardCorePlayer///
    SU<bool> HardCorePlayer(true, { "HardCorePlayer", "Enabled" });
    SU<bool> FoodEnhance(true, { "HardCorePlayer", "FoodEnhance", "Enabled" });
    SU<jsonDictVector> FoodList({{{"name", "minecraft:apple"}, {"point", 4}}}, { "HardCorePlayer", "FoodEnhance", "List" });

    ///fishingMonster///
    SU<bool> FishingMonster(true, { "FishingMonster", "Enabled" });
    SU<double> FishingMonsterPersentage(0.5,{ "FishingMonster", "Persentage" });
    SU<jsonDictVector> FishingMonsterTypeList({ {{"type", "minecraft:zombie"}, {"chance", 1.0}} }, { "FishingMonster", "TypeList" });
    std::vector<double> FishingMonsterchances;

    ///superCreeper///
    SU<bool> SuperCreeper(true, { "SuperCreeper", "Enabled" });


    void checkChance()
    {
        double totalChance = 0.0;
        for (const auto& item : FishingMonsterTypeList)
        {
            totalChance += item.at("chance").get<double>();
        }
        if (totalChance != 1.0)
        {
            for (auto& item : FishingMonsterTypeList)
            {
                item["chance"] = item.at("chance").get<double>() / totalChance;
            }
        }
        for (const auto& monsterType : FishingMonsterTypeList)
        {
            FishingMonsterchances.push_back(monsterType.at("chance").get<double>());
        }
    }


    nlohmann::json globalJson()
    {
        nlohmann::json json;
        HardCorePlayer.save(json);
        FoodEnhance.save(json);
        FoodList.save(json);
        FishingMonster.save(json);
        FishingMonsterPersentage.save(json);
        FishingMonsterTypeList.save(json);
        SuperCreeper.save(json);
        return json;
    }

    void initjson(nlohmann::json json)
    {
        HardCorePlayer.load(json);
        FoodEnhance.load(json);
        FoodList.load(json);
        FishingMonster.load(json);
        FishingMonsterPersentage.load(json);
        FishingMonsterTypeList.load(json);
        SuperCreeper.load(json);
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