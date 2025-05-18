#ifndef __CREATURE__
#define __CREATURE__

#include "Entity.h"

class Room;

class Creature : public Entity {
	int health;
	int attackPower;
	int armor;
	int baseDamage;
	int level;
	CreatureTypes creatureType;

public:
	Creature(CreatureTypes creatureType, const string& name, const string& description);
	~Creature() override;

	int getHealth() const;

	int getAttackPower() const;

	int getArmor() const;

	int getDamage() const;

	int getLevel() const;

	void setHealth(int amount);

	void setAttackPower(int amount);

	void setArmor(int amount);

	void setLevel(int lvl);

	// This is to check if creature is friendly, enemy or player
	const CreatureTypes& getCreatureType() const;

	bool isAlive() const;

	// Takes damage depending on the level difference between the 2 entities
	// Higher level gets less damage - Lower level gets increased damage
	int takeDamage(int amount, int levelDifference);

};

#endif