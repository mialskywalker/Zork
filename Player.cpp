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

	// checks and returns entity if it is in inventory -> return nullptr if it's not
}

Entity* Player::getEntity(const string& name) {
	for (const auto& c : currentRoom->getContains()) {
		if (c->getName() == name) {
			return c;
		}
	}
	return nullptr;

	// checks and returns entity if it is in room -> return nullptr if it's not
}

void Player::listInventory() {
	if (getContains().size())
	{
		cout << "You are carrying:" << endl;
		listEntities();
		// prints inventory if player has items
	}
	else
		cout << "You aren't carrying anything!" << endl;
		// if no items in inventory
}

void Player::move(const Direction& direction) {
	for (Entity* e : currentRoom->getContains()) {
		if (e->getType() == Type::EXIT) {
			Exit* exit = dynamic_cast<Exit*>(e);
			if (exit->getDirection() == direction) {
				if (!exit->getIsLocked()) {
					// if exit is found and unlocked - move player
					setCurrentRoom(exit->getDestination());
					cout << "You move to " << getRoom()->getName() << endl;
					return;
				}
				// if exit is found and locked
				cout << exit->getDestination()->getName() << " is locked. You need to find a key!" << endl;
				return;
			}
		}
	}
	// no matching exit in that direction
	cout << "You can't go that way!" << endl;
}

void Player::use(const string& itemName) {
	Entity* item = getItem(itemName);

	if (auto potion = dynamic_cast<Potion*>(item)) {
		if (potion->useItem(this))
			remove(item);
		// if item is potion - use and remove from inventory
	}
	else if (item) {
		cout << "You can't use that item." << endl;
		// if item is not a potion
	}
	else {
		cout << "Item not found." << endl;
		// if item is not in inventory
	}
}

void Player::take(const string& itemName) {
	Entity* entity = getEntity(itemName);
	if (auto item = dynamic_cast<Item*>(entity)) {
		if (item->getName() == itemName) {
			add(item);
			cout << item->getDescription() << " added to inventory!" << endl;
			getRoom()->remove(entity);
			return;
			// if entity is found and is an item - add to inventory and remove from room
		}
	}
	
	cout << "I can't find that item." << endl;
	// if entity is not an item or doesn't exist in room
}

void Player::drop(const string& itemName) {
	Item* item = dynamic_cast<Item*>(getItem(itemName));

	if (item->getEquipped()) {
		unequip(item->getName());
		// if item is equipped - unequip it first
	}

	if (item != nullptr) {
		getRoom()->add(item);
		cout << item->getDescription() << " dropped!" << endl;
		remove(item);
		// if item is valid - add it to the room and remove from inventory
	}
	else {
		cout << "I don't have that item." << endl;
		// if item not in inventory
	}
}

void Player::equip(const string& itemName) {
	Item* item = dynamic_cast<Item*>(getItem(itemName));

	if (!item) {
		cout << "Item not found!" << endl;
		return;
		// if item is nullptr - do nothing
	}
	
	// WEAPON
	if (item->getItemType() == ItemTypes::WEAPON) {
		Weapon* weapon = dynamic_cast<Weapon*>(item);

		if (weapon->getReqLevel() > getLevel()) {
			cout << "You need to be level " << weapon->getReqLevel() << " to equip this item!" << endl;
			return;
			// if weapon requires higher level than the player currently is
		}

		if (!weapon->getEquipped()) {
			if (currentWeapon != nullptr) {
				unequip(currentWeapon->getName());
				// if there is already a weapon in that slot
			}
			weapon->equipItem();
			setAttackPower(getAttackPower() + weapon->getDamage());
			currentWeapon = weapon;
			cout << "Equipped: " << itemName << endl;
			// equip weapon and add it's stats to the player
		}
		else {
			cout << "Item is already equipped!" << endl;
			// if that weapon is already equipped
		}
	}
	// ARMOR
	else if (item->getItemType() == ItemTypes::ARMOR) {
		Armor* armor = dynamic_cast<Armor*>(item);

		if (armor->getReqLevel() > getLevel()) {
			cout << "You need to be level " << armor->getReqLevel() << " to equip this item!" << endl;
			return;
			// if armor requires higher level than the player currently is
		}

		if (!armor->getEquipped()) {
			if (currentArmor != nullptr) {
				unequip(currentArmor->getName());
				// if there is already an armor in that slot
			}
			armor->equipItem();
			setArmor(getArmor() + armor->getArmor());
			currentArmor = armor;
			cout << "Equipped: " << itemName << endl;
			// equip armor and add it's stats to the player
		}
		else {
			cout << "Item is already equipped!" << endl;
			// if that armor is already equipped
		}
	}
	else {
		cout << "Item not equippable!" << endl;
		// if item is not weapon or armor -> key, potion etc.
	}
}

void Player::unequip(const string& itemName) {
	Item* item = dynamic_cast<Item*>(getItem(itemName));

	if (!item) {
		cout << "Item not found!" << endl;
		return;
		// item is nullptr
	}

	// WEAPON
	if (item->getItemType() == ItemTypes::WEAPON) {
		Weapon* weapon = dynamic_cast<Weapon*>(item);

		if (weapon->getEquipped()) {
			weapon->unequipItem();
			setAttackPower(getAttackPower() - weapon->getDamage());
			currentWeapon = nullptr;
			cout << "Unequipped: " << itemName << endl;
			// if weapon is equipped - unequip it, remove weapon stats from player and set weapon slot to nullptr
		}
		else {
			cout << "Item not equipped!" << endl;
			// weapon not equipped
		}
	}
	// ARMOR
	else if (item->getItemType() == ItemTypes::ARMOR) {
		Armor* armor = dynamic_cast<Armor*>(item);

		if (armor->getEquipped()) {
			armor->unequipItem();
			setArmor(getArmor() - armor->getArmor());
			currentArmor = nullptr;
			cout << "Unequipped: " << itemName << endl;
			// if armor is equipped - unequip it, remove armor stats from player and set armor slot to nullptr
		}
		else {
			cout << "Item not equipped!" << endl;
			// armor not equipped
		}
	}
	else {
		cout << "Invalid item." << endl;
		// item not weapon or armor | or item doesn't exist in inventory
	}
}

void Player::open(const string& itemName) {
	Item* item = dynamic_cast<Item*>(getEntity(itemName));

	if (!item) {
		cout << "Nothing to open!" << endl;
		return;
		// item == nullptr
	}

	if (item->getItemType() == ItemTypes::CHEST) {
		Chest* chest = dynamic_cast<Chest*>(item);
		if (chest->getIsLocked()) {
			cout << "The " << chest->getName() << " is locked! You need a key." << endl;
			return;
			// item is chest and it's locked
		}
		if (chest->getContains().size() <= 0) {
			cout << "The " << chest->getName() << " is empty!" << endl;
			chest->useChest(this);
			return;
			// item is chest and is empty
		}
		cout << "You find:" << endl;
		chest->listEntities();
		chest->useChest(this);
		// show chest contents and interact with it
	}
	else {
		cout << "I cannot open that" << endl;
		// item is not a chest
	}
}

void Player::unlock(const string& name) {
	Entity* entity = getEntity(name);
	bool keyFound = false;

	if (!entity) {
		cout << "Nothing to unlock!" << endl;
		return;
		// entity == nullptr
	}

	if (auto chest = dynamic_cast<Chest*>(entity)) {
		// entity is chest
		int requiredId = chest->getId();
		for (const auto& i : getContains()) {
			if (auto key = dynamic_cast<Key*>(i)) {
				keyFound = true;
				if (key->getId() == requiredId) {
					chest->unlock(requiredId);
					return;
					// iterates through inventory to find a key with same id as chest
					// if found and keyId == chest requiredId - unlock the chest
				}
			}
		}
		if (keyFound) {
			cout << "Key not compatible" << endl;
			return;
			// keyId != chest requiredId
		}
		
		cout << "I don't have a key" << endl;
		// no keys in inventory
	}
	else if (auto exit = dynamic_cast<Exit*>(entity)) {
		// entity is exit
		int requiredId = exit->getId();
		for (const auto& i : getContains()) {
			if (auto key = dynamic_cast<Key*>(i)) {
				keyFound = true;
				if (key->getId() == requiredId) {
					exit->unlock(requiredId);
					return;
					// iterates through inventory to find a key with same id as exit
					// if found and keyId == exit requiredId - unlock the exit
				}
			}
		}

		if (keyFound) {
			cout << "Key not compatible" << endl;
			return;
			// keyId != chest requiredId
		}

		cout << "I don't have a key" << endl;
		// no keys in inventory
	}

	cout << "I can't unlock that!" << endl;
	// entity is not a chest or an exit
}

void Player::lock(const string& name) {
	Entity* entity = getEntity(name);
	bool keyFound = false;

	if (!entity) {
		cout << "Nothing to unlock!" << endl;
		return;
		// entity == nullptr
	}

	if (auto chest = dynamic_cast<Chest*>(entity)) {
		// entity is chest
		int requiredId = chest->getId();
		for (const auto& i : getContains()) {
			if (auto key = dynamic_cast<Key*>(i)) {
				keyFound = true;
				if (key->getId() == requiredId) {
					chest->lock(requiredId);
					return;
					// iterates through inventory to find a key with same id as chest
					// if found and keyId == chest requiredId - lock the chest
				}
			}
		}

		if (keyFound) {
			cout << "Key not compatible" << endl;
			return;
			// keyId != chest requiredId
		}

		cout << "I don't have a key" << endl;
		// no keys in inventory
	}

	else if (auto exit = dynamic_cast<Exit*>(entity)) {
		// entity is exit
		int requiredId = exit->getId();
		for (const auto& i : getContains()) {
			if (auto key = dynamic_cast<Key*>(i)) {
				if (key->getId() == requiredId) {
					exit->lock(requiredId);
					return;
					// iterates through inventory to find a key with same id as exit
					// if found and keyId == exit requiredId - lock the exit
				}
			}
		}

		if (keyFound) {
			cout << "Key not compatible" << endl;
			return;
			// keyId != exit requiredId
		}

		cout << "I don't have a key" << endl;
		// no keys in inventory
	}

	cout << "I can't lock that!" << endl;
	// entity not lockable
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
		// creature == nullptr
	}

	if (creature->getCreatureType() != CreatureTypes::ENEMY) {
		cout << "You can't attack that target!" << endl;
		return;
		// creature not an enemy - do nothing
	}

	Enemy* enemy = dynamic_cast<Enemy*>(creature);
	bool enemyIsStronger = enemy->getLevel() > getLevel();
	int enemyLevelDifference = enemy->getLevel() - getLevel();
	int playerLevelDifference = getLevel() - enemy->getLevel();
	// calculate the level difference between player and enemy
	
	// if player level > enemy level - enemy takes more damage
	// if player level == enemy level - take normal damage
	// if player level < enemy level - take less damage
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
		// enemy dead - drop items + player gains XP + enemy is removed from the room
	}
	else {
		// if player level > enemy level - player takes less damage
		// if player level == enemy level - take normal damage
		// if player level < enemy level - player takes more damage
		amount = takeDamage(enemy->getDamage(), enemyLevelDifference);
		cout << "The " << enemy->getName() << " hits you (";
		cout << getHealth() << " HP) back for " << amount;
		cout << " damage!" << endl;
		if (!isAlive()) {
			cout << "You have been slain!" << endl;
			// player is dead -> end game
		}
	}
}

void Player::levelUp() {
	setLevel(getLevel() + 1);
	if (getXP() - getLevelRequiredXP() < 0)
		setXP(0);
	else
		setXP(getXP() - getLevelRequiredXP());
	setLevelRequiredXP(getLevelRequiredXP() + 50);
	setMaxHealth(getMaxHealth() + 25);
	setHealth(getMaxHealth());
	setAttackPower(getAttackPower() + 10);
	setArmor(getArmor() + 10);
	cout << "You have reached level " << getLevel() << "!" << endl;

	// player levels up - required xp for next level increased, max health + attack power + armor also increased | health set to new max health value
}

void Player::gainXP(int amount, int levelDifference) {
	// player gains less XP if higher level than enemy
	// player gains more XP if lower level than enemy
	if (levelDifference < 0)
		amount /= -levelDifference;
	else if (levelDifference > 0)
		amount *= levelDifference;
	int totalXP = getXP() + amount;
	setXP(totalXP);
	cout << "You gained " << amount << "XP!" << endl;
	while (getXP() - getLevelRequiredXP() >= 0)
		levelUp();
	// if XP is more than required for level up - add the remainder to the new level
	// if still more - keep leveling up until totalXP gained <= 0
	
}