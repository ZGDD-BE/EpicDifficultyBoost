#include <global.h>

namespace HardCorePlayer {
	void eatFood(Player* player, ItemStack* item) {
		if (settings::Foods.find(item->getTypeName()) != settings::Foods.end()) {
			player->heal(settings::Foods[item->getTypeName()]);
		}
	}
}