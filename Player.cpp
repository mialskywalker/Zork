#include <iostream>
#include "Player.h"
#include "Room.h"
#include "Exit.h"
#include "Potion.h"
#include "Weapon.h"
#include "Armor.h"
#include "Enemy.h"

Player::Player() :
	Creature("Player", "A great adventurer!") {
	currentWeapon = nullptr;
	currentArmor = nullptr;
}

Player::~Player() {}

const Room* Player::getRoom() const { return this->currentRoom; }

void Player::setCurrentRoom(Room* room) {
	this->currentRoom = room;
}

Entity* Player::getItem(const string& name) {
	for (const auto& i : getContains()) {
		if (i->getName() == name) {
			return i;
		}
	}
	return nullptr;
}

Entity* Player::getCreature(const string& name) {
	for (const auto& c : currentRoom->getContains()) {
		if (c->getName() == name) {
			return c;
		}
	}
	return nullptr;
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

	if (item->getDescription() == "Weapon" || item->getDescription() == "Armor") {
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

	if (!item) {
		cout << "Item not found!" << endl;
		return;
	}
	
	if (item->getDescription() == "Weapon") {
		Weapon* weapon = dynamic_cast<Weapon*>(item);
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
	else if (item->getDescription() == "Armor") {
		Armor* armor = dynamic_cast<Armor*>(item);
		if (!armor->getEquipped()) {
			if (currentArmor != nullptr) {
				unequip(currentArmor->getName());
			}
			armor->equipItem();
			setArmor(getArmor() + armor->getArmor());
			currentArmor = armor;
			cout << "Equipped: " << itemName << endl;
		}
		else {
			cout << "Item is already equipped!" << endl;
		}
	}
	else {
		cout << "Item not equippable!" << endl;
	}
}

void Player::unequip(const string& itemName) {
	Entity* item = getItem(itemName);

	if (!item) {
		cout << "Item not found!" << endl;
		return;
	}

	if (item->getDescription() == "Weapon") {
		Weapon* weapon = dynamic_cast<Weapon*>(item);

		if (weapon->getEquipped()) {
			weapon->unequipItem();
			setAttackPower(getAttackPower() - weapon->getDamage());
			currentWeapon = nullptr;
			cout << "Unequipped: " << itemName << endl;
		}
		else {
			cout << "Item not equipped!" << endl;
		}
	}
	else if (item->getDescription() == "Armor") {
		Armor* armor = dynamic_cast<Armor*>(item);

		if (armor->getEquipped()) {
			armor->unequipItem();
			setArmor(getArmor() - armor->getArmor());
			currentArmor = nullptr;
			cout << "Unequipped: " << itemName << endl;
		}
		else {
			cout << "Item not equipped!" << endl;
		}
	}
	else {
		cout << "Invalid item." << endl;
	}
}

void Player::showStatus() {
	cout << "-----------------------------------" << endl;
	cout << "HP: " << this->getHealth() << endl;
	cout << "Attack Power: " << this->getAttackPower() << endl;
	cout << "Armor: " << this->getArmor() << endl;
	cout << "-----------------------------------" << endl;
}

void Player::attack(const string& enemyName) {
	Entity* creature = getCreature(enemyName);

	if (!creature) {
		cout << "You don't have a target!" << endl;
		return;
	}

	if (creature->getDescription() != "Hostile") {
		cout << "You can't attack that target!" << endl;
		return;
	}

	Enemy* enemy = dynamic_cast<Enemy*>(creature);
	int amount = enemy->takeDamage(getDamage());
	cout << "You hit the " << enemy->getName() << " (";
	cout << enemy->getHealth() << "HP) for " << amount;
	cout << " damage!" << endl;
	if (!enemy->isAlive()) {
		cout << "You defeated " << enemy->getName() << endl;
		currentRoom->remove(creature);
		return;
	}
	else {
		amount = takeDamage(enemy->getDamage());
		cout << "The " << enemy->getName() << " hits you (";
		cout << getHealth() << " HP) back for " << amount;
		cout << " damage!" << endl;
		if (!isAlive()) {
			cout << "You have been slain!" << endl;
		}
	}
}