#ifndef __ENEMY__
#define __ENEMY__

#include "NPC.h"

class Enemy : public NPC {
	int xpYield;
public:
	Enemy(const string& name, int hp, int attackPower);
	~Enemy() override;

	int getXPYield() const;

	void setXPYield(int amount);

	void drop(Room* room);
};

#endif