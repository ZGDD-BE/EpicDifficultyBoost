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

	void healthTick(Player* player) {
		//logger.info("2333");
		if (!playersTickTime[player->getXuid()]) {
			playersTickTime[player->getXuid()] = 0;
		}
		playersTickTime[player->getXuid()] += 1;
		db = std::make_unique<SQLite::Database>(PluginDatabase, SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
		if (playersTickTime[player->getXuid()] % (20*60) == 0)
		{
			int time = 1;
			std::string xuid = player->getXuid();
			SQLite::Statement query(*db, "SELECT TIMES FROM Players WHERE XUID = ?");
			query.bind(1, xuid);

			int currentTimes = 0;
			if (query.executeStep()) {
				currentTimes = query.getColumn(0);
			}

			int newTimes = currentTimes + time;
			SQLite::Statement insert(*db, "INSERT OR REPLACE INTO Players(XUID, TIMES) VALUES(?, ?)");
			insert.bind(1, xuid);
			insert.bind(2, newTimes);
			insert.exec();
			playersTickTime[player->getXuid()] = 0;
		}

	}
}