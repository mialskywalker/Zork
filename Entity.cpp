#include <iostream>
#include "Entity.h"

Entity::Entity(const Type type, const string& name, const string& description) :
	type(type),
	name(name),
	description(description) { }

Entity::~Entity() {
	contains.clear();
}

Type Entity::getType() const { return this->type; }

const string& Entity::getName() const { return this->name; }

const string& Entity::getDescription() const { return this->description; }

list<Entity*>& Entity::getContains() { return this->contains; }

void Entity::add(Entity* entity) {
	if (entity->getType() != Type::EXIT) {
		contains.push_back(entity);
		// adds all entities to the list except for exits - there is a different function in room that links exits to rooms
	}
}

void Entity::remove(Entity* entity) {
	for (auto it = contains.begin(); it != contains.end(); ++it) {
		if (*it == entity) {
			contains.erase(it);
			break;
			// removes an entity from the list if found
		}
	}
}

void Entity::listEntities() const {
	for (const auto& c : this->contains)
		cout << "- " << c->getDescription() << " " << c->getInfo() << "   (" << c->getName() << ")" << endl;
	// if entity contains entities in the list - prints info | else it is skipped
}
