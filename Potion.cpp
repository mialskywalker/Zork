#include <iostream>
#include "Potion.h"
#include "Player.h"

Potion::Potion(const string& name, const string& description, const string& stat, int amount) :
	Item(name, ItemTypes::POTION, description),
	stat(stat),
	amount(amount) { }

Potion::~Potion() {}

const string& Potion::getStat() const { return this->stat; }

int Potion::getAmount() const { return this->amount; }

bool Potion::useItem(Player* player) {
	if (getStat() == "HP") {
		if (player->getHealth() < player->getMaxHealth()) {
			int currentAmount = player->getMaxHealth() - player->getHealth();
			player->setHealth(currentAmount);
			cout << "Healed for " << currentAmount << "HP" << endl;
			return true;
		}
		else {
			cout << "Health is already full" << endl;
			return false;
		}
	}
	else if (getStat() == "AttackPower") {
		player->setAttackPower(player->getAttackPower() + getAmount());
		cout << "Attack Power increased by " << getAmount() << endl;
		return true;
	}
	else if (getStat() == "Stamina") {
		player->setMaxHealth(player->getMaxHealth() + getAmount());
		player->setHealth(player->getMaxHealth());
		cout << "Max Health increased to " << player->getMaxHealth() << endl;
		return true;
	}
	return false;
}