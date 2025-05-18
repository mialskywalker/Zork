#include <iostream>
#include "Enemy.h"
#include "Room.h"

Enemy::Enemy(const string& name, const string& description, int hp, int attackPower, int xpYield) :
	Creature(CreatureTypes::ENEMY, name, description),
	xpYield(xpYield) {
	setHealth(hp);
	setAttackPower(attackPower);
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
			cout << "* " << i->getDescription() << " dropped!" << endl;
			room->add(i);
		}
		getContains().clear();
	}
}

string Enemy::getInfo() const {
	return "[Level " + to_string(getLevel()) + "]";
}