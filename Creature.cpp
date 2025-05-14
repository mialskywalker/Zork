#include "Creature.h"

Creature::Creature(const string& name, const string& description) :
	Entity(Type::CREATURE, name, description) {
	this->health = 100;
	this->attackPower = 0;
	this->armor = 0;
	this->baseDamage = 10;
}

Creature::~Creature() {
}

int Creature::getHealth() const { return this->health; }

int Creature::getAttackPower() const { return this->attackPower; }

int Creature::getArmor() const { return this->armor; }

int Creature::getDamage() const { return this->baseDamage + (this->attackPower / 10); }

void Creature::setHealth(int amount) {
	this->health = amount;
}

void Creature::setAttackPower(int amount) {
	this->attackPower = amount;
}

void Creature::setArmor(int amount) {
	this->armor = amount;
}

bool Creature::isAlive() const {
	return getHealth() > 0;
}