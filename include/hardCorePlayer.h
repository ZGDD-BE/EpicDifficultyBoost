#include <global.h>

namespace HardCorePlayer {
	void hungerTick(Player* player);
	void eatFood(Player* player, ItemStack* item);
	void healthTick(Player* player);
	void loadDefaultHealth(Player* player);
	void hungerToHealth(Player* player);
}