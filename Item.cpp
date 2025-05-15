#include "Item.h"

Item::Item(const string& name, ItemTypes itemType, const string& description) :
	Entity(Type::ITEM, name, description),
	itemType(itemType) { }

Item::~Item() {}

const ItemTypes& Item::getItemType() const { return this->itemType; }