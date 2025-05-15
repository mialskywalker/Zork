#include <iostream>
#include "Enemy.h"
#include "Room.h"

Enemy::Enemy(const string& name, const string& description, int hp, int attackPower) :
	Creature(CreatureTypes::ENEMY, name, description) {
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