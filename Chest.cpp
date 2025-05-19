#include <iostream>
#include <string>
#include <sstream>
#include "Chest.h"
#include "Player.h"

Chest::Chest(const string& name, const string& description, bool isLocked, int id) :
	Item(name, ItemTypes::CHEST, description),
	isLocked(isLocked),
	id(id) { }

Chest::~Chest() {}

Item* Chest::getItem(const string& name) {
	for (const auto& i : getContains()) {
		if (i->getName() == name) {
			// return a pointer to the item with the given name if it exists in the chest 
			return dynamic_cast<Item*>(i);
		}
	}
	// return nullptr if not found or if entity is not an item
	return nullptr;
}

int Chest::getId() const { return this->id; }

bool Chest::getIsLocked() const { return this->isLocked; }

void Chest::placeItem(Item* item) {
	// if item is not nullptr -> add it to chest list
	if (item) {
		cout << item->getName() << " placed into the " << getName() << endl;
		add(item);
		return;
	}
	cout << "You can't place that" << endl;
}

void Chest::useChest(Player* player) {
	// parses and executes the player's input command
	string input;
	cout << ">>>> ";
	getline(cin, input);
	istringstream iss(input);
	string command, arg;
	iss >> command;
	bool bFirst = true;
	string res = "";
	// extracts and returns the remainig arguments from a command input stream | Example: "take wooden sword" - returns "wooden sword"
	while (iss >> arg) {
		if (bFirst) {
			res += arg;
			bFirst = false;
		}
		else {
			res += ' ' + arg;
		}
	}
	if (command == "take") {
		Item* item = getItem(res);
		if (!item) {
			cout << "Item not in " << getName() << endl;
			return;
		}
		// if item is nullptr print and do nothing
		cout << item->getName() << " added to inventory!" << endl;
		player->add(item);
		remove(item);
		// if item is found in the chest - add to player inventory and remove from chest
	}
	else if (command == "place") {
		// get item from player inventory
		Item* item = dynamic_cast<Item*>(player->getItem(res));

		if (item->getEquipped()) {
			player->unequip(item->getName());
		}
		// if item is equipped - unequip it
		// if item is not nullptr - add it to the chest and remove from player inventory
		if (item != nullptr) {
			placeItem(item);
			player->remove(item);
		}
		else {
			cout << "You don't have that item." << endl;
		}
	}
	else {
		cout << "Invalid command." << endl;
	}
	// after each command - player closes the chest 
	cout << "You close the " << getName() << endl;
	return;
}

void Chest::unlock(int keyId) {
	if (!getIsLocked()) {
		cout << getName() << " is not locked!" << endl;
		return;
	}
	// if chest is not locked print and do nothing | if locked - unlock

	this->isLocked = false;
	cout << getName() << " successfully unlocked!" << endl;
}

void Chest::lock(int keyId) {
	if (getIsLocked()) {
		cout << getName() << " is already locked!" << endl;
		return;
	}
	// if chest is locked print and do nothing | if unlocked - lock

	this->isLocked = true;
	cout << getName() << " successfully locked!" << endl;
}

string Chest::getInfo() const {
	return "[" + string(getIsLocked() ? "Locked" : "Unlocked") + "]";
}

