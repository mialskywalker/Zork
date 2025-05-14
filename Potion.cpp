#include <iostream>
#include "Potion.h"
#include "Player.h"

Potion::Potion(const string& name, const string& description, const string& stat, int amount) :
	Item(name, description),
	stat(stat),
	amount(amount) { }

Potion::~Potion() {}

const string& Potion::getStat() const { return this->stat; }

int Potion::getAmount() { return this->amount; }

void Potion::useItem(Player* player) {
	if (getStat() == "HP") {
		if (getAmount() + player->getHealth() >= 100) {
			int currentAmount = 100 - player->getHealth();
			player->setHealth(100);
			cout << "Healed for " << currentAmount << "HP" << endl;
		}
		else {
			player->setHealth(player->getHealth() + getAmount());
			cout << "Healed for " << getAmount() << "HP" << endl;
		}
	}
}