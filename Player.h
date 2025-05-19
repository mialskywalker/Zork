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

	~Player() override;

	Room* getRoom() const;

	// Sets the room the player is in
	void setCurrentRoom(Room* room);

	// return current XP
	int getXP() const;

	// set current XP
	void setXP(int amount);

	// returns the required XP to level up
	int getLevelRequiredXP() const;

	// sets the required XP to level up
	void setLevelRequiredXP(int amount);

	// returns the maximum health possible for the player to have at this level
	int getMaxHealth() const;

	// sets the maximum health possible for the player to have at this level (increases each level)
	void setMaxHealth(int amount);

	// returns Entity contained in inventory
	Entity* getItem(const string& name);

	// returns Entity contained in room
	Entity* getEntity(const string& name);

	// print items in inventory
	void listInventory();

	void move(const Direction& direction);

	// can be used on potions only
	void use(const string& itemName);

	// pick up item from room
	void take(const string& itemName);

	// drop item from inventory to room - if item is equipped - unequip first then drop
	void drop(const string& itemName);

	// equip item from inventory
	void equip(const string& itemName);

	// unequip item from inventory
	void unequip(const string& itemName);

	// opens chests
	void open(const string& itemName);

	// unlocks chests or exits
	void unlock(const string& name);

	// locks chests or exits
	void lock(const string& name);

	// shows current player level, xp, health, attack power, armor, damage
	void showStatus();

	// hits enemy - enemy hits back if not dead
	void attack(const string& enemyName);

	// increases player level + stats
	void levelUp();

	// gains XP depending on the level difference between the 2 entities
	// if enemy is higher level - player gains more xp when enemy dies
	// else player gains less xp
	void gainXP(int amount, int levelDifference);

};

#endif