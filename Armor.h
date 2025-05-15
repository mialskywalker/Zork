#ifndef __ARMOR__
#define __ARMOR__

#include "Item.h"

class Armor : public Item {
	int armor;
	int reqLevel;
	bool equipped;

public:
	Armor(const string& name, const string& description, const int armor, const int reqLevel);
	~Armor();

	int getArmor() const;

	int getReqLevel() const;

	bool getEquipped() const;

	void equipItem();

	void unequipItem();
};

#endif