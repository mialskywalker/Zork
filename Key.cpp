#include "Key.h"

Key::Key(const string& name, const string& description, int id) :
	Item(name, ItemTypes::KEY, description),
	id(id) { }

Key::~Key() {}

int Key::getId() const { return this->id; }
