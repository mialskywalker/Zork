#ifndef __CHEST__
#define __CHEST__

#include "Item.h"

class Player;

class Chest : public Item {
	int id;
	bool isLocked;
public:
	Chest(const string& name, const string& description, bool isLocked, int id);
	~Chest() override;
	
	// Return an item contained in the Chest
	Item* getItem(const string& name);

	int getId() const;

	bool getIsLocked() const;

	// Add item to the Chest
	void placeItem(Item* item);

	// Interact with chest - take item or place item
	void useChest(Player* player);

	// Lock and unlock require keyId == id
	void unlock(int keyId);

	void lock(int keyId);

	string getInfo() const override;
};

#endif