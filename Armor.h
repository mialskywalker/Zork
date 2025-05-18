#ifndef __ARMOR__
#define __ARMOR__

#include "Item.h"

class Armor : public Item {
	int armor;
	int reqLevel;
	bool equipped;

public:
	Armor(const string& name, const string& description, const int armor, const int reqLevel);
	~Armor() override;

	int getArmor() const;

	// Returns the required player level to use this item
	int getReqLevel() const;

	bool getEquipped() const override;

	string getInfo() const override;

	void equipItem();

	void unequipItem();

};

#endif