#include <iostream>
#include <string>
#include <sstream>
#include "Chest.h"
#include "Player.h"

Chest::Chest(const string& name, const string& description) :
	Item(name, ItemTypes::CHEST, description) { }

Chest::~Chest() {}

Item* Chest::getItem(const string& name) {
	for (const auto& i : getContains()) {
		if (i->getName() == name) {
			return dynamic_cast<Item*>(i);
		}
	}
	return nullptr;
}

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
	cout << ">> ";
	getline(cin, input);
	istringstream iss(input);
	string command, arg;
	iss >> command;

	if (command == "take") {
		iss >> arg;
		Item* item = getItem(arg);
		if (!item) {
			cout << "Item not in " << getName() << endl;
			return;
		}

		cout << item->getName() << " added to inventory!" << endl;
		player->add(item);
		remove(item);
	}
	else if (command == "drop") {
		iss >> arg;
		Item* item = dynamic_cast<Item*>(player->getItem(arg));

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
		cout << "You close the " << getName() << endl;
		return;
	}
}

