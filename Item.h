#ifndef __ITEM__
#define __ITEM__

#include "Entity.h"

class Item : public Entity {
public:
	Item(const string& name, const string& description);
	~Item() override;
	Item(const Item&) = delete;
	Item& operator=(const Item&) = delete;
	Item(Item&&) = default;
	Item& operator=(Item&&) = default;
};

#endif