#ifndef __ARMOR__
#define __ARMOR__

#include "Item.h"

class Armor : public Item {
	int armor;
	bool equipped;

public:
	Armor(const string& name, const string& description, const int armor);
	~Armor();

	int getArmor() const;

	bool getEquipped() const;

	void equipItem();

	void unequipItem();
};

#endif