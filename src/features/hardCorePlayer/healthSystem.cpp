#include <global.h>
#include <version.h>
static std::unique_ptr<SQLite::Database> db;
namespace HardCorePlayer {
	std::unordered_map<std::string, int> playersTickTime;
	void eatFood(Player* player, ItemStack* item) {
		if (settings::Foods.find(item->getTypeName()) != settings::Foods.end()) {
			player->heal(settings::Foods[item->getTypeName()]);
		}
	}

	int getPlayerAliveTime(Player* player) {
		std::string xuid = player->getXuid();
		if (db == nullptr)
			db = std::make_unique<SQLite::Database>(PluginDatabase, SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
		SQLite::Statement query(*db, "SELECT TIMES FROM Players WHERE XUID = ?");
		query.bind(1, xuid);

		int currentTimes = 0;
		if (query.executeStep()) {
			currentTimes = query.getColumn(0);
		}

		return currentTimes;
	}

	void healthTick(Player* player) {
		//logger.info("2333");
		if (!playersTickTime[player->getXuid()]) {
			playersTickTime[player->getXuid()] = 0;
		}
		playersTickTime[player->getXuid()] += 1;
		db = std::make_unique<SQLite::Database>(PluginDatabase, SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
		if (playersTickTime[player->getXuid()] % (20 * 60) == 0)
		{
			auto ti = getPlayerAliveTime(player);
			SQLite::Statement insert(*db, "INSERT OR REPLACE INTO Players(XUID, TIMES) VALUES(?, ?)");
			insert.bind(1, player->getXuid());
			insert.bind(2, ti + 1);
			insert.exec();
			playersTickTime[player->getXuid()] = 0;
			if (const_cast<AttributeInstance&>(player->getAttribute(Attribute::getByName("minecraft:health"))).getMaxValue() < 20.0f)
			{
				auto hp = (settings::NormalHealthPoint + int((ti + 1) / 60) < 20) ? settings::NormalHealthPoint + int((ti + 1) / 60) : 20;
				const_cast<AttributeInstance&>(player->getAttribute(Attribute::getByName("minecraft:health"))).setMaxValue(hp);
			}
		}

	}


	void loadDefaultHealth(Player* player) {
		if (getPlayerAliveTime(player) < 1)
			const_cast<AttributeInstance&>(player->getAttribute(Attribute::getByName("minecraft:health"))).setMaxValue(settings::NormalHealthPoint);
		}
}