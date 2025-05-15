#ifndef __ENEMY__
#define __ENEMY__

#include "NPC.h"

class Enemy : public NPC {
public:
	Enemy(const string& name, int hp, int attackPower);
	~Enemy() override;
};

#endif