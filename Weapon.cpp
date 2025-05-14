#include "Weapon.h"

Weapon::Weapon(const string& name, const string& description, const int damage) :
	Item(name, description),
	damage(damage) {
	this->equipped = false;
}

Weapon::~Weapon() {}

int Weapon::getDamage() const { return this->damage; }

bool Weapon::getEquipped() const { return this->equipped; }

void Weapon::equipItem() {
	this->equipped = true;
}

void Weapon::unequipItem() {
	this->equipped = false;
}