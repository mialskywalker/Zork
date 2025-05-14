#ifndef __PLAYER__
#define __PLAYER__

#include "Creature.h"
#include "Globals.h"

class Weapon;

class Player : public Creature {
	Weapon* currentWeapon;
public:
	Room* currentRoom = nullptr;

	Player();

	~Player();

	// Getters and Setters

	const Room* getRoom() const;

	void setCurrentRoom(Room* room);

	// Methods

	void move(const Direction& direction);

	Entity* getItem(const string& name);

	void use(const string& itemName);

	void take(const string& itemName);

	void drop(const string& itemName);

	void equip(const string& itemName);

	void unequip(const string& itemName);

	void showStatus();

};

#endif