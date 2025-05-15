#include <iostream>
#include "Enemy.h"
#include "Room.h"

Enemy::Enemy(const string& name, int hp, int attackPower) :
	NPC(name, "Hostile", "") {
	setHealth(hp);
	setAttackPower(attackPower);
	setXPYield(10);
}

Enemy::~Enemy() {}

int Enemy::getXPYield() const { return this->xpYield; }

void Enemy::setXPYield(int amount) {
	this->xpYield = amount;
}

void Enemy::drop(Room* room) {
	if (!isAlive())
	{
		for (auto& i : getContains()) {
			cout << "* " << i->getName() << " dropped!" << endl;
			room->add(i);
		}
		getContains().clear();
	}
}