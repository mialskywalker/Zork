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

	const CreatureTypes& getCreatureType() const;

	bool isAlive() const;

	int takeDamage(int amount, int levelDifference);

};

#endif