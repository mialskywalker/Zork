#include "Armor.h"

Armor::Armor(const string& name, const string& description, const int armor, const int reqLevel) :
	Item(name, ItemTypes::ARMOR, description),
	armor(armor),
	reqLevel(reqLevel) {
	this->equipped = false;
}

Armor::~Armor() {}

int Armor::getArmor() const { return this->armor; }

int Armor::getReqLevel() const { return this->reqLevel; }

bool Armor::getEquipped() const { return this->equipped; }

string Armor::getInfo() const {
	return "[Armor: " + to_string(getArmor()) + "| Requires level " + to_string(getReqLevel()) + "| " + (getEquipped() ? "Equipped" : "Not equipped") + "]";
}

void Armor::equipItem() {
	this->equipped = true;
}

void Armor::unequipItem() {
	this->equipped = false;
}