#include <iostream>
#include "Player.h"
#include "Room.h"
#include "Exit.h"
#include "Potion.h"

Player::Player() :
	Creature("Player", "A great adventurer!") { }

Player::~Player() {}

const Room* Player::getRoom() const { return this->currentRoom; }

void Player::setCurrentRoom(Room* room) {
	this->currentRoom = room;
}

void Player::move(const Direction& direction) {
	for (Entity* e : currentRoom->getContains()) {
		if (e->getType() == Type::EXIT) {
			Exit* exit = static_cast<Exit*>(e);
			if (exit->getDirection() == direction) {
				currentRoom = exit->getDestination();
				cout << "You move to " << currentRoom->getName() << endl;
				return;
			}
		}
	}
	cout << "You can't go that way!" << endl;
}

Entity* Player::getItem(const string& name) {
	for (const auto& i : getContains()) {
		if (i->getName() == name) {
			return i;
		}
	}
	return nullptr;
}

void Player::use(const string& itemName) {
	Entity* item = getItem(itemName);

	if (auto potion = dynamic_cast<Potion*>(item)) {
		potion->useItem(this);
		this->remove(item);
	}
	else if (item) {
		cout << "You can't use that item." << endl;
	}
	else {
		cout << "Item not found." << endl;
	}
}

void Player::take(const string& itemName) {
	for (auto& i : this->currentRoom->getContains()) {
		if (auto item = dynamic_cast<Item*>(i)) {
			if (item->getName() == itemName) {
				this->add(item);
				cout << item->getName() << " added to inventory!" << endl;
				this->currentRoom->remove(i);
				return;
			}
		}
	}
	cout << "I can't find that item." << endl;
}

void Player::drop(const string& itemName) {
	Entity* item = getItem(itemName);

	if (item != nullptr) {
		this->currentRoom->add(item);
		cout << item->getName() << " dropped!" << endl;
		this->remove(item);
	}
	else {
		cout << "I don't have that item." << endl;
	}
}