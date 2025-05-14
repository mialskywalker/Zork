#ifndef __WEAPON__
#define __WEAPON__

#include "Item.h"

class Weapon : public Item {
	int damage;
	bool equipped;

public:
	Weapon(const string& name, const string& description, const int damage);
	~Weapon();
	
	int getDamage() const;

	bool getEquipped() const;

	void equipItem();

	void unequipItem();
};

#endif