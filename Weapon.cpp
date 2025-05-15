#include "Weapon.h"

Weapon::Weapon(const string& name, const string& description, const int damage, const int reqLevel) :
	Item(name, description),
	damage(damage),
	reqLevel(reqLevel) {
	this->equipped = false;
}

Weapon::~Weapon() {}

int Weapon::getDamage() const { return this->damage; }

int Weapon::getReqLevel() const { return this->reqLevel; }

bool Weapon::getEquipped() const { return this->equipped; }

void Weapon::equipItem() {
	this->equipped = true;
}

void Weapon::unequipItem() {
	this->equipped = false;
}