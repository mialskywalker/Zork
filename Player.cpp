#include <iostream>
#include "Player.h"
#include "Room.h"
#include "Exit.h"
#include "Potion.h"
#include "Weapon.h"
#include "Armor.h"
#include "Enemy.h"
#include "Chest.h"
#include "Key.h"

Player::Player() :
	Creature(CreatureTypes::PLAYER, "Player", "A great adventurer!") {
	currentWeapon = nullptr;
	currentArmor = nullptr;
	xp = 0;
	levelRequiredXp = 100;
	maxHealth = 100;
}

Player::~Player() {}

Room* Player::getRoom() const { return this->currentRoom; }

void Player::setCurrentRoom(Room* room) {
	this->currentRoom = room;
}

int Player::getXP() const { return this->xp; }

void Player::setXP(int amount) {
	this->xp = amount;
}

int Player::getLevelRequiredXP() const { return this->levelRequiredXp; }

void Player::setLevelRequiredXP(int amount) {
	this->levelRequiredXp = amount;
}

int Player::getMaxHealth() const { return this->maxHealth; }

void Player::setMaxHealth(int amount) {
	this->maxHealth = amount;
}

Entity* Player::getItem(const string& name) {
	for (const auto& i : getContains()) {
		if (i->getName() == name) {
			return i;
		}
	}
	return nullptr;
}

Entity* Player::getEntity(const string& name) {
	for (const auto& c : currentRoom->getContains()) {
		if (c->getName() == name) {
			return c;
		}
	}
	return nullptr;
}

void Player::listInventory() {
	if (getContains().size())
	{
		cout << "You are carrying:" << endl;
		listEntities();
	}
	else
		cout << "You aren't carrying anything!" << endl;
}

void Player::move(const Direction& direction) {
	for (Entity* e : currentRoom->getContains()) {
		if (e->getType() == Type::EXIT) {
			Exit* exit = dynamic_cast<Exit*>(e);
			if (exit->getDirection() == direction) {
				if (!exit->getIsLocked()) {
					setCurrentRoom(exit->getDestination());
					cout << "You move to " << getRoom()->getName() << endl;
					return;
				}
				cout << exit->getDestination()->getName() << " is locked. You need to find a key!" << endl;
				return;
			}
		}
	}
	cout << "You can't go that way!" << endl;
}

void Player::use(const string& itemName) {
	Entity* item = getItem(itemName);

	if (auto potion = dynamic_cast<Potion*>(item)) {
		if (potion->useItem(this))
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
	for (auto& i : getRoom()->getContains()) {
		if (auto item = dynamic_cast<Item*>(i)) {
			if (item->getName() == itemName) {
				add(item);
				cout << item->getDescription() << " added to inventory!" << endl;
				getRoom()->remove(i);
				return;
			}
		}
	}
	cout << "I can't find that item." << endl;
}

void Player::drop(const string& itemName) {
	Item* item = dynamic_cast<Item*>(getItem(itemName));

	if (item->getEquipped()) {
		unequip(item->getName());
	}

	if (item != nullptr) {
		getRoom()->add(item);
		cout << item->getDescription() << " dropped!" << endl;
		remove(item);
	}
	else {
		cout << "I don't have that item." << endl;
	}
}

void Player::equip(const string& itemName) {
	Item* item = dynamic_cast<Item*>(getItem(itemName));

	if (!item) {
		cout << "Item not found!" << endl;
		return;
	}
	
	if (item->getItemType() == ItemTypes::WEAPON) {
		Weapon* weapon = dynamic_cast<Weapon*>(item);

		if (weapon->getReqLevel() > getLevel()) {
			cout << "You need to be level " << weapon->getReqLevel() << " to equip this item!" << endl;
			return;
		}

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
	else if (item->getItemType() == ItemTypes::ARMOR) {
		Armor* armor = dynamic_cast<Armor*>(item);

		if (armor->getReqLevel() > getLevel()) {
			cout << "You need to be level " << armor->getReqLevel() << " to equip this item!" << endl;
			return;
		}

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
	Item* item = dynamic_cast<Item*>(getItem(itemName));

	if (!item) {
		cout << "Item not found!" << endl;
		return;
	}

	if (item->getItemType() == ItemTypes::WEAPON) {
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
	else if (item->getItemType() == ItemTypes::ARMOR) {
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

void Player::open(const string& itemName) {
	Item* item = dynamic_cast<Item*>(getEntity(itemName));

	if (!item) {
		cout << "Nothing to open!" << endl;
		return;
	}

	if (item->getItemType() == ItemTypes::CHEST) {
		Chest* chest = dynamic_cast<Chest*>(item);
		if (chest->getIsLocked()) {
			cout << "The " << chest->getName() << " is locked! You need a key." << endl;
			return;
		}
		if (chest->getContains().size() <= 0) {
			cout << "The " << chest->getName() << " is empty!" << endl;
			chest->useChest(this);
			return;
		}
		cout << "You find:" << endl;
		chest->listEntities();
		chest->useChest(this);
	}
	else {
		cout << "I cannot open that" << endl;
	}
}

void Player::unlock(const string& name) {
	Entity* entity = getEntity(name);

	if (!entity) {
		cout << "Nothing to unlock!" << endl;
		return;
	}

	if (auto chest = dynamic_cast<Chest*>(entity)) {

		int requiredId = chest->getId();
		for (const auto& i : getContains()) {
			if (auto key = dynamic_cast<Key*>(i)) {
				if (key->getId() == requiredId) {
					chest->unlock(requiredId);
					return;
				}
			}
		}

		cout << "Key not compatible" << endl;
		return;
	}
	else if (auto exit = dynamic_cast<Exit*>(entity)) {
		int requiredId = exit->getId();
		for (const auto& i : getContains()) {
			if (auto key = dynamic_cast<Key*>(i)) {
				if (key->getId() == requiredId) {
					exit->unlock(requiredId);
					return;
				}
			}
		}

		cout << "Key not compatible" << endl;
		return;
	}

	cout << "I can't unlock that!" << endl;
}

void Player::lock(const string& name) {
	Entity* entity = getEntity(name);

	if (!entity) {
		cout << "Nothing to unlock!" << endl;
		return;
	}

	if (auto chest = dynamic_cast<Chest*>(entity)) {

		int requiredId = chest->getId();
		for (const auto& i : getContains()) {
			if (auto key = dynamic_cast<Key*>(i)) {
				if (key->getId() == requiredId) {
					chest->lock(requiredId);
					return;
				}
			}
		}

		cout << "Key not compatible" << endl;
		return;
	}

	else if (auto exit = dynamic_cast<Exit*>(entity)) {
		int requiredId = exit->getId();
		for (const auto& i : getContains()) {
			if (auto key = dynamic_cast<Key*>(i)) {
				if (key->getId() == requiredId) {
					exit->lock(requiredId);
					return;
				}
			}
		}

		cout << "Key not compatible" << endl;
		return;
	}

	cout << "I can't lock that!" << endl;
}

void Player::showStatus() {
	cout << "-----------------------------------" << endl;
	cout << "Level: " << getLevel() << endl;
	cout << "XP: " << getXP() << "/" << getLevelRequiredXP() << endl;
	cout << "HP: " << getHealth() << endl;
	cout << "Attack Power: " << getAttackPower() << endl;
	cout << "Armor: " << getArmor() << endl;
	cout << "-----------------------------------" << endl;
}

void Player::attack(const string& enemyName) {
	Creature* creature = dynamic_cast<Creature*>(getEntity(enemyName));

	if (!creature) {
		cout << "You don't have a target!" << endl;
		return;
	}

	if (creature->getCreatureType() != CreatureTypes::ENEMY) {
		cout << "You can't attack that target!" << endl;
		return;
	}

	Enemy* enemy = dynamic_cast<Enemy*>(creature);
	bool enemyIsStronger = enemy->getLevel() > getLevel();
	int enemyLevelDifference = enemy->getLevel() - getLevel();
	int playerLevelDifference = getLevel() - enemy->getLevel();

	int amount = enemy->takeDamage(getDamage(), playerLevelDifference);
	cout << "You hit the " << enemy->getName() << " (";
	cout << enemy->getHealth() << "HP) for " << amount;
	cout << " damage!" << endl;
	if (!enemy->isAlive()) {
		cout << "You defeated " << enemy->getName() << endl;
		enemy->drop(getRoom());
		gainXP(enemy->getXPYield(), enemyLevelDifference);
		currentRoom->remove(creature);
		return;
	}
	else {
		amount = takeDamage(enemy->getDamage(), enemyLevelDifference);
		cout << "The " << enemy->getName() << " hits you (";
		cout << getHealth() << " HP) back for " << amount;
		cout << " damage!" << endl;
		if (!isAlive()) {
			cout << "You have been slain!" << endl;
		}
	}
}

void Player::gainXP(int amount, int levelDifference) {
	if (levelDifference < 0)
		amount /= -levelDifference;
	else if (levelDifference > 0)
		amount *= levelDifference;
	int totalXP = getXP() + amount;
	setXP(totalXP);
	cout << "You gained " << amount << "XP!" << endl;

	while (getXP() - getLevelRequiredXP() >= 0) {
		setLevel(getLevel() + 1);
		setXP(getXP() - getLevelRequiredXP());
		setLevelRequiredXP(getLevelRequiredXP() + 50);
		setMaxHealth(getMaxHealth() + 25);
		setHealth(getMaxHealth());
		setAttackPower(getAttackPower() + 10);
		setArmor(getArmor() + 10);
		cout << "You have reached level " << getLevel() << "!" << endl;
	}
}