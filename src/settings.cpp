#include <global.h>
#include <settings.h>
#include <llapi/utils/FileHelper.h>

namespace settings
{
    ///hardCorePlayer///
    SU<bool> HardCorePlayer(true, { "HardCorePlayer", "Enabled" });
    SU<bool> FoodEnhance(true, { "HardCorePlayer", "FoodEnhance", "Enabled" });
    SU<bool> NormalHealth(true, { "HardCorePlayer", "NormalHealth", "Enabled" });
    SU<int> NormalHealthPoint(10, { "HardCorePlayer", "NormalHealth", "Point" });
    SU<jsonDictVector> FoodList({{{"name", "minecraft:apple"}, {"point", 4}}}, { "HardCorePlayer", "FoodEnhance", "List" });
    std::unordered_map<std::string,int> Foods;

    ///fishingMonster///
    SU<bool> FishingMonster(true, { "FishingMonster", "Enabled" });
    SU<double> FishingMonsterPersentage(0.5,{ "FishingMonster", "Persentage" });
    SU<jsonDictVector> FishingMonsterTypeList({ {{"type", "minecraft:zombie"}, {"chance", 1.0}} }, { "FishingMonster", "TypeList" });
    std::vector<double> FishingMonsterchances;

    ///superCreeper///
    SU<bool> SuperCreeper(true, { "SuperCreeper", "Enabled" });

    ///superSkeleton///
    SU<bool> SuperSkeleton(true, { "SuperSkeleton", "Enabled" });
    SU<int> SuperSkeletonSpeedLimit(10, { "SuperSkeleton", "SpeedLimit" });

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

    void toFoods() {
        for (const auto& item : FoodList) 
        {
            Foods[item.at("name").get<std::string>()] = item.at("point").get<int>();
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
        SuperSkeleton.save(json);
        SuperSkeletonSpeedLimit.save(json);
        NormalHealth.save(json);
        NormalHealthPoint.save(json);
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
        SuperSkeleton.load(json);
        SuperSkeletonSpeedLimit.load(json);
        NormalHealth.load(json);
        NormalHealthPoint.load(json);
        checkChance();
        toFoods();
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