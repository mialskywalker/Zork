#ifndef __PLAYER__
#define __PLAYER__

#include "Creature.h"
#include "Globals.h"

class Weapon;
class Armor;

class Player : public Creature {
	Weapon* currentWeapon;
	Armor* currentArmor;
	int xp;
	int levelRequiredXp;
	int maxHealth;

public:
	Room* currentRoom = nullptr;

	Player();

	~Player();

	// Getters and Setters

	const Room* getRoom() const;

	void setCurrentRoom(Room* room);

	int getXP() const;

	void setXP(int amount);

	int getLevelRequiredXP() const;

	void setLevelRequiredXP(int amount);

	int getMaxHealth() const;

	void setMaxHealth(int amount);

	// Methods

	Entity* getItem(const string& name);

	Entity* getCreature(const string& name);

	void move(const Direction& direction);

	void use(const string& itemName);

	void take(const string& itemName);

	void drop(const string& itemName);

	void equip(const string& itemName);

	void unequip(const string& itemName);

	void showStatus();

	void attack(const string& enemyName);

	void gainXP(int amount, int levelDifference);

};

#endif