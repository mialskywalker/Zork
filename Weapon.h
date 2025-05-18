#ifndef __WEAPON__
#define __WEAPON__

#include "Item.h"

class Weapon : public Item {
	int damage;
	int reqLevel;
	bool equipped;

public:
	Weapon(const string& name, const string& description, const int damage, const int reqLevel);
	~Weapon() override;
	
	int getDamage() const;

	int getReqLevel() const;

	bool getEquipped() const override;

	string getInfo() const override;

	void equipItem();

	void unequipItem();

};

#endif