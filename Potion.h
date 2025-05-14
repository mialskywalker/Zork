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
	Potion(const Potion&) = delete;
	Potion& operator=(const Potion&) = delete;
	Potion(Potion&&) = default;
	Potion& operator=(Potion&&) = default;

	const string& getStat() const;

	int getAmount() const;

	void useItem(Player* player);
};

#endif