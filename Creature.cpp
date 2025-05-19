#include "time.h"
#include "Creature.h"

Creature::Creature(CreatureTypes creatureType, const string& name, const string& description) :
	creatureType(creatureType),
	Entity(Type::CREATURE, name, description) {
	this->health = 100;
	this->attackPower = 0;
	this->armor = 0;
	this->baseDamage = 10;
	this->level = 1;
}

Creature::~Creature() {
}

int Creature::getHealth() const { 
	if (this->health <= 0)
		return 0;
	return this->health;
}

int Creature::getAttackPower() const { return this->attackPower; }

int Creature::getArmor() const { return this->armor; }

int Creature::getDamage() const { return this->baseDamage + (this->attackPower / 10); }

int Creature::getLevel() const { return this->level; }

void Creature::setHealth(int amount) {
	this->health = amount;
}

void Creature::setAttackPower(int amount) {
	this->attackPower = amount;
}

void Creature::setArmor(int amount) {
	this->armor = amount;
}

void Creature::setLevel(int lvl) {
	this->level = lvl;
}

const CreatureTypes& Creature::getCreatureType() const { return this->creatureType; }

bool Creature::isAlive() const {
	return getHealth() > 0;
	// if health is greater than 0 returns true | if less or equal return false
}

int Creature::takeDamage(int amount, int levelDifference) {
	// random seed
	srand(time(0));

	if (levelDifference <= 0)
		levelDifference = 1;
	// if level difference is negative set to 1

	int damageAmount = (amount + (levelDifference * 2)) + (rand() % amount - (armor / 10));
	// calculate damage based on level difference and armor

	setHealth(getHealth() - damageAmount);
	return damageAmount;
	// return damage to print the amount
}
