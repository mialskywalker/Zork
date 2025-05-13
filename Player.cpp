#include <iostream>
#include "Player.h"
#include "Room.h"
#include "Exit.h"

Player::Player() :
	Creature("Player", "A great adventurer!") { }

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