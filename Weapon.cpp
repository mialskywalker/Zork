#include "Weapon.h"

Weapon::Weapon(const string& name, const string& description, const int damage, const int reqLevel) :
	Item(name, ItemTypes::WEAPON, description),
	damage(damage),
	reqLevel(reqLevel) {
	this->equipped = false;
}

Weapon::~Weapon() {}

int Weapon::getDamage() const { return this->damage; }

int Weapon::getReqLevel() const { return this->reqLevel; }

bool Weapon::getEquipped() const { return this->equipped; }

string Weapon::getInfo() const {
	return "[Damage: " + to_string(getDamage()) + "| Requires level " + to_string(getReqLevel()) + "| " + (getEquipped() ? "Equipped" : "Not equipped") + "]";
}

void Weapon::equipItem() {
	this->equipped = true;
}

void Weapon::unequipItem() {
	this->equipped = false;
}