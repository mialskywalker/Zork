#ifndef __ENEMY__
#define __ENEMY__

#include "Creature.h"

class Enemy : public Creature {
	int xpYield;
public:
	Enemy(const string& name, const string& description, int hp, int attackPower);
	~Enemy() override;

	int getXPYield() const;

	void setXPYield(int amount);

	void drop(Room* room);
};

#endif