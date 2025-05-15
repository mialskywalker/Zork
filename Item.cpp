#include "Item.h"

Item::Item(const string& name, const string& description) :
	Entity(Type::ITEM, name, description) { }

Item::~Item() {}
