#ifndef __ITEM__
#define __ITEM__

#include "Entity.h"

class Item : public Entity {
	ItemTypes itemType;
public:
	Item(const string& name, ItemTypes itemType, const string& description);
	~Item() override;

	// Returns true if the item is equipped
	virtual bool getEquipped() const { return false; }

	const ItemTypes& getItemType() const;

};

#endif