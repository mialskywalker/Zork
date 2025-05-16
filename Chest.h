#ifndef __CHEST__
#define __CHEST__

#include "Item.h"

class Player;

class Chest : public Item {
public:
	Chest(const string& name, const string& description);
	~Chest() override;
	Chest(const Chest&) = delete;
	Chest& operator=(const Chest&) = delete;
	Chest(Chest&&) = default;
	Chest& operator=(Chest&&) = default;

	Item* getItem(const string& name);

	void placeItem(Item* item);

	void useChest(Player* player);
};

#endif