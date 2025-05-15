#include "Enemy.h"


Enemy::Enemy(const string& name, int hp, int attackPower) :
	NPC(name, "Hostile", "") {
	setHealth(hp);
	setAttackPower(attackPower);
}

Enemy::~Enemy() {}