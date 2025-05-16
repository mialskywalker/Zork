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

	const string& getStat() const;

	int getAmount() const;

	bool useItem(Player* player);
};

#endif