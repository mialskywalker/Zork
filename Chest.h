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
	
	Item* getItem(const string& name);

	int getId() const;

	bool getIsLocked() const;

	void placeItem(Item* item);

	void useChest(Player* player);

	void unlock(int keyId);

	void lock(int keyId);

	string getInfo() const override;
};

#endif