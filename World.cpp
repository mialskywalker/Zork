#include <iostream>
#include "World.h"
#include "Room.h"
#include "Exit.h"
#include "Player.h"
#include "NPC.h"
#include "Potion.h"
#include "Weapon.h"
#include "Armor.h"
#include "Enemy.h"

World::World() {
	isRunning = true;
	setUpWorld();
}

World::~World() {
	for (Entity* e : entities)
		delete e;
	entities.clear();
}

void World::addEntity(Entity* entity) {
	entities.push_back(entity);
}

void World::removeEntity(Entity* entity) {
	if (entities.size()) {
		for (int i = 0; i < entities.size(); i++) {
			if (entities[i] == entity) {
				entities.erase(entities.begin() + i);
				delete entity;
				break;
			}
		}
	}
}

void World::run() {
	cout << "Welcome to the world of adventure!" << endl;

	while (isRunning) {
		if (!player->isAlive())
			break;
		cout << endl << ">> ";
		string input;
		getline(cin, input);
		processCommand(input);
	}
}

void World::setUpWorld() {
	NPC* gosho = new NPC("hooded figure", "A hooded figure leans calmly against the wall, their eyes kind but alert - clearly not a threat.", "Thank godness you're alive!");
	Enemy* orc = new Enemy("orc", "A hulking orc snarls in your direction, gripping a crude blade. Fresh blood drips from its tusks.", 50, 150);


	orc->setLevel(5);
	orc->setXPYield(150);
	addEntity(gosho);
	addEntity(orc);

	Potion* hp = new Potion("vial", "A small glass vial filled with crimson liquid pulses faintly, as if alive - clearly meant to restore vitality.", "HP", 0);
	Weapon* sword = new Weapon("sword", "A slightly rusted longsword lies on the ground behind the chair, its hilt still faintly warm to the touch.", 50, 1);
	Weapon* axe = new Weapon("axe", "A heavy iron axe rests against the wall, its blade chipped but still deadly from countless battles.", 70, 2);
	Armor* helmet = new Armor("helmet", "A dented iron helmet sits atop a crate, its visor cracked but still capable of offering some protection.", 110, 1);
	Armor* bracers = new Armor("bracers", "Worn leather bracers lay folded near a torn sack, stained with sweat and scorched from old spells.", 75, 2);

	addEntity(hp);
	addEntity(sword);
	addEntity(helmet);
	addEntity(axe);
	addEntity(bracers);
	orc->add(axe);

	Room* room = new Room("Entrance", "This is an open field");
	Room* room2 = new Room("Hallway", "Second room");
	addEntity(room);
	addEntity(room2);

	Exit* northExit = new Exit("north", "To the north, dense trees form a shadowy forest. The wind rustles the leaves with a whisper, hinting at secrets hidden beneath the canopy.", room, room2, Direction::NORTH);
	Exit* southExit = new Exit("south", "To the south, cracked stone pillars rise from the earth - remnants of some forgotten structure cloaked in dust and silence.", room2, room, Direction::SOUTH);
	addEntity(northExit);
	addEntity(southExit);

	room->add(gosho);
	room->add(hp);
	room->add(sword);
	room->add(helmet);
	room->add(bracers);
	room->addExit(northExit);
	room2->addExit(southExit);
	room->add(orc);

	player = new Player();
	player->setCurrentRoom(room);
	addEntity(player);

}

string World::getCommandArgs(istringstream& iss) {
	bool bFirst = true;
	string res = "";
	string arg;
	while (iss >> arg) {
		if (bFirst) {
			res += arg;
			bFirst = false;
		}
		else {
			res += ' ' + arg;
		}
	}
	return res;
}

void World::processCommand(const string& input) {
	istringstream iss(input);
	string command, arg;
	iss >> command;

	if (command == "look") {
		cout << player->getRoom()->getName() << endl;
		cout << player->getRoom()->getDescription() << endl;
		cout << "You see:" << endl;
		player->getRoom()->listEntities();
	}
	else if (command == "go") {
		iss >> arg;
		
		if (arg == "east") {
			player->move(Direction::EAST);
		}
		else if (arg == "west") {
			player->move(Direction::WEST);
		}
		else if (arg == "north") {
			player->move(Direction::NORTH);
		}
		else if (arg == "south") {
			player->move(Direction::SOUTH);
		}
		else {
			cout << "You can't go that way!" << endl;
		}
	}
	else if (command == "inventory") {
		player->listInventory();
	}
	else if (command == "talk") {
		string npcName = getCommandArgs(iss);
		bool isValidNPC = false;
		for (const auto& e : player->getRoom()->getContains()) {
			if (auto npc = dynamic_cast<NPC*>(e)) {
				if (npc->getName() == npcName)
				{
					isValidNPC = true;
					cout << npc->getName() << ": " << npc->getDialogue() << endl;
				}
			}
		}
		if (!isValidNPC)
			cout << npcName << " is not currently here." << endl;
	}
	else if (command == "take") {
		string itemName = getCommandArgs(iss);
		player->take(itemName);
	}
	else if (command == "drop") {
		string itemName = getCommandArgs(iss);
		player->drop(itemName);
	}
	else if (command == "use") {
		string itemName = getCommandArgs(iss);
		player->use(itemName);
	}
	else if (command == "equip") {
		string itemName = getCommandArgs(iss);
		player->equip(itemName);
	}
	else if (command == "unequip") {
		string itemName = getCommandArgs(iss);
		player->unequip(itemName);
	}
	else if (command == "status") {
		player->showStatus();
	}
	else if (command == "attack") {
		string enemyName = getCommandArgs(iss);
		player->attack(enemyName);
	}
	else if (command == "quit") {
		isRunning = false;
		cout << "Thank you for playing! See you soon!" << endl;
	}
	else {
		cout << "Invalid command!" << endl;
	}
}
