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
			return dynamic_cast<Item*>(i);
		}
	}
	return nullptr;
}

int Chest::getId() const { return this->id; }

bool Chest::getIsLocked() const { return this->isLocked; }

void Chest::placeItem(Item* item) {
	if (item) {
		cout << item->getName() << " placed into the " << getName() << endl;
		add(item);
		return;
	}
	cout << "I can't place that" << endl;
}

void Chest::useChest(Player* player) {
	string input;
	cout << ">>>> ";
	getline(cin, input);
	istringstream iss(input);
	string command, arg;
	iss >> command;
	bool bFirst = true;
	string res = "";
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

		cout << item->getName() << " added to inventory!" << endl;
		player->add(item);
		remove(item);
	}
	else if (command == "place") {
		Item* item = dynamic_cast<Item*>(player->getItem(res));

		if (item->getEquipped()) {
			player->unequip(item->getName());
		}

		if (item != nullptr) {
			placeItem(item);
			player->remove(item);
		}
		else {
			cout << "I don't have that item." << endl;
		}
	}
	else {
		cout << "Invalid command." << endl;
	}
	
	cout << "You close the " << getName() << endl;
	return;
}

void Chest::unlock(int keyId) {
	if (!getIsLocked()) {
		cout << getName() << " is not locked!" << endl;
		return;
	}

	this->isLocked = false;
	cout << getName() << " successfully unlocked!" << endl;
}

void Chest::lock(int keyId) {
	if (getIsLocked()) {
		cout << getName() << " is already locked!" << endl;
		return;
	}

	this->isLocked = true;
	cout << getName() << " successfully locked!" << endl;
}

string Chest::getInfo() const {
	return "[" + string(getIsLocked() ? "Locked" : "Unlocked") + "]";
}

