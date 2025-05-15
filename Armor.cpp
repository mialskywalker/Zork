#include "Armor.h"

Armor::Armor(const string& name, const string& description, const int armor, const int reqLevel) :
	Item(name, description),
	armor(armor),
	reqLevel(reqLevel) {
	this->equipped = false;
}

Armor::~Armor() {}

int Armor::getArmor() const { return this->armor; }

int Armor::getReqLevel() const { return this->reqLevel; }

bool Armor::getEquipped() const { return this->equipped; }

void Armor::equipItem() {
	this->equipped = true;
}

void Armor::unequipItem() {
	this->equipped = false;
}