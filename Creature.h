#ifndef __CREATURE__
#define __CREATURE__

#include "Entity.h"

class Room;

class Creature : public Entity {
	int health;
	int attackPower;
	int armor;
	int baseDamage;

public:
	Creature(const string& name, const string& description);
	~Creature() override;
	Creature(const Creature&) = delete;
	Creature& operator=(const Creature&) = delete;
	Creature(Creature&&) = default;
	Creature& operator=(Creature&&) = default;

	// Getters and Setters

	int getHealth() const;

	int getAttackPower() const;

	int getArmor() const;

	int getDamage() const;

	void setHealth(int amount);

	void setAttackPower(int amount);

	void setArmor(int amount);

	// Methods

	bool isAlive() const;

	int takeDamage(int amount);

};

#endif