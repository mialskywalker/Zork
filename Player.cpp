#include <iostream>
#include "Player.h"
#include "Room.h"
#include "Exit.h"
#include "Potion.h"
#include "Weapon.h"

Player::Player() :
	Creature("Player", "A great adventurer!") {
	currentWeapon = nullptr;
}

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
		remove(item);
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
				add(item);
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

	if (item->getDescription() == "Weapon") {
		unequip(item->getName());
	}

	if (item != nullptr) {
		this->currentRoom->add(item);
		cout << item->getName() << " dropped!" << endl;
		remove(item);
	}
	else {
		cout << "I don't have that item." << endl;
	}
}

void Player::equip(const string& itemName) {
	Entity* item = getItem(itemName);
	
	if (item->getDescription() == "Weapon") {
		if (auto weapon = dynamic_cast<Weapon*>(item)) {
			if (!weapon->getEquipped()) {
				if (currentWeapon != nullptr) {
					unequip(currentWeapon->getName());
				}
				weapon->equipItem();
				setAttackPower(getAttackPower() + weapon->getDamage());
				currentWeapon = weapon;
				cout << "Equipped: " << itemName << endl;
			}
			else {
				cout << "Item is already equipped!" << endl;
			}
		}
		else {
			cout << "Item not found!" << endl;
		}
	}
	else {
		cout << "Item not equippable!" << endl;
	}
}

void Player::unequip(const string& itemName) {
	Entity* item = getItem(itemName);

	if (item->getDescription() == "Weapon") {
		if (auto weapon = dynamic_cast<Weapon*>(item)) {
			if (weapon->getEquipped()) {
				if (currentWeapon == nullptr) {
					cout << "Item not equipped!" << endl;
				}
				else {
					weapon->unequipItem();
					setAttackPower(getAttackPower() - weapon->getDamage());
					currentWeapon = nullptr;
					cout << "Unequipped: " << itemName << endl;
				}

			}
			else {
				cout << "Item not equipped!" << endl;
			}
		}
		else {
			cout << "Item not found!" << endl;
		}
	}
	else {
		cout << "Item not equipped!" << endl;
	}
}

void Player::showStatus() {
	cout << "-----------------------------------" << endl;
	cout << "HP: " << this->getHealth() << endl;
	cout << "Attack Power: " << this->getAttackPower() << endl;
	cout << "Armor: " << this->getArmor() << endl;
	cout << "-----------------------------------" << endl;
}