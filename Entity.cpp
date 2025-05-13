#include "Entity.h"

Entity::Entity(const Type type, const string name, const string description) :
	type(type),
	name(name),
	description(description) { }

Entity::~Entity() {
	for (Entity* e : contains)
		delete e;
}

Type Entity::getType() const { return this->type; }

const string& Entity::getName() const { return this->name; }

const string& Entity::getDescription() const { return this->description; }

list<Entity*>& Entity::getContains() { return this->contains; }
