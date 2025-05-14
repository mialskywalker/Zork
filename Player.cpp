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

void Player::use(const string& itemName) {
	for (const auto& i : getContains()) {
		if (i->getDescription() == "Potion" && i->getName() == itemName) {
			Potion* potion = dynamic_cast<Potion*>(i);
			potion->useItem(this);
		}
	}
}