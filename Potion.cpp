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
			player->setHealth(player->getMaxHealth());
			cout << "Healed for " << currentAmount << "HP" << endl;
			return true;
			// use potion if player health is not full and return true
			// heal the player to full health and show the amount healed
		}
		else {
			cout << "Health is already full" << endl;
			return false;
			// returns false - potion is not used and is still in inventory
		}
	}
	else if (getStat() == "AttackPower") {
		player->setAttackPower(player->getAttackPower() + getAmount());
		cout << "Attack Power increased by " << getAmount() << endl;
		return true;
		// increase player attack power with the amount - potion is used
	}
	else if (getStat() == "Stamina") {
		player->setMaxHealth(player->getMaxHealth() + getAmount());
		player->setHealth(player->getMaxHealth());
		cout << "Max Health increased to " << player->getMaxHealth() << endl;
		return true;
		// increase player max health with the amount - potion is used
		// set player health value to max health
	}
	return false;
	// safe return if invalid
}