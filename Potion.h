#ifndef __POTION__
#define __POTION__

#include "Item.h"

class Player;

class Potion : public Item {
	string stat;
	int amount;

public:
	Potion(const string& name, const string& description, const string& stat, int amount);
	~Potion() override;

	// returns a string with the player stat which is going to be increased
	const string& getStat() const;

	int getAmount() const;

	// returns true if item is successfully used - and is removed from inventory
	// if false - item is kept in inventory
	bool useItem(Player* player);
};

#endif