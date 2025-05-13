#include "Creature.h"

Creature::Creature(const string& name, const string& description) :
	Entity(Type::CREATURE, name, description) {
	this->health = 100;
}

Creature::~Creature() {
}

int Creature::getHealth() const { return this->health; }

void Creature::setHealth(int amount) {
	this->health = amount;
}

bool Creature::isAlive() const {
	return getHealth() > 0;
}