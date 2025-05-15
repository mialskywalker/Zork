#include "Armor.h"

Armor::Armor(const string& name, const string& description, const int armor) :
	Item(name, description),
	armor(armor) {
	this->equipped = false;
}

Armor::~Armor() {}

int Armor::getArmor() const { return this->armor; }

bool Armor::getEquipped() const { return this->equipped; }

void Armor::equipItem() {
	this->equipped = true;
}

void Armor::unequipItem() {
	this->equipped = false;
}