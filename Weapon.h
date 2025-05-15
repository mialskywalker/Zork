#ifndef __WEAPON__
#define __WEAPON__

#include "Item.h"

class Weapon : public Item {
	int damage;
	int reqLevel;
	bool equipped;

public:
	Weapon(const string& name, const string& description, const int damage, const int reqLevel);
	~Weapon();
	
	int getDamage() const;

	int getReqLevel() const;

	bool getEquipped() const;

	void equipItem();

	void unequipItem();
};

#endif