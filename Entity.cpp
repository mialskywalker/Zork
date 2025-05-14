#include "Entity.h"
#include <iostream>

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
		contains.push_back(std::move(entity));
	}
}

void Entity::remove(Entity* entity) {
	for (auto it = contains.begin(); it != contains.end(); ++it) {
		if (*it == entity) {
			contains.erase(it);
			break;
		}
	}
}

void Entity::listEntities() const {
	if (this->contains.size()) {
		for (const auto& c : this->contains)
			cout << "- " << c->getName() << " (" << c->getDescription() << ")" << endl;
	}
}
