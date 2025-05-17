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
#include "Chest.h"
#include "Key.h"

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
	cout << "Press Enter to begin your journey, or type 'skip' to jump ahead" << endl;
	cout << ">> ";
	string input;
	getline(cin, input);
	if (input != "skip")
		showIntro();

	while (isRunning) {
		if (!player->isAlive())
			break;
		cout << endl << ">> ";
		getline(cin, input);
		processCommand(input);
	}
}

void World::setUpWorld() {


	// ROOMS
	Room* safeHouse = new Room("Safe House", "A quiet stone shelter, dimly lit by a flickering lantern. Dust hangs in the air. A lone villager watches over you.");
	Room* villageCenter = new Room("Village Center", "Cracked cobblestone paths split in four directions. The village is eerily quiet, with signs of recent struggle.");
	Room* forest = new Room("Forest", "Twisted trees and thick underbrush surround you. The wind howls unnaturally through the branches.");
	Room* graveyard = new Room("Graveyard", "Cracked gravestones and open coffins litter the cursed ground. A chill seeps into your bones.");
	Room* blacksmith = new Room("Blacksmith Workshop", "The forge glows faintly. Tools lie scattered across the floor, and something lurks in the back.");
	Room* castleRoad = new Room("Castle Road", "The path here is lined with fallen banners and cracked statues. The castle looms in the distance.");
	Room* castleHall = new Room("Castle Hall", "Tall stone columns line the grand hall. At its center stands the necromancer, cloaked in shadows.");
	Room* gravekeeperHouse = new Room("Gravekeeper's House", "The smell of decay clings to the air. Ritual tools and bones are scattered across the floor.");
	Room* alchemistLab = new Room("Alchemist Lab", "Broken shelves and smashed vials litter the floor. A few intact potions remain on a glowing table.");

	// EXITS
	// Safe House <-> Village Center
	Exit* houseDoorN = new Exit("north", "A reinforced wooden door leads to the outside world.", safeHouse, villageCenter, Direction::NORTH, false, 0);
	Exit* houseDoorS = new Exit("south", "Door to the Safe House", villageCenter, safeHouse, Direction::SOUTH, false, 0);
	// Village Center <-> Forest
	Exit* centerToForest = new Exit("east", "A narrow, overgrown path leads into the dark trees.", villageCenter, forest, Direction::EAST, false, 1);
	Exit* forestToCenter = new Exit("west", "The overgrown trail leads back to the village square.", forest, villageCenter, Direction::WEST, false, 1);
	// Village Center <-> Blacksmith Workshop
	Exit* centerToBlacksmith = new Exit("west", "You hear faint metal clanging from behind thick wooden shutters.", villageCenter, blacksmith, Direction::WEST, false, 2);
	Exit* blacksmithToCenter = new Exit("east", "The metal-reinforced door leads back to the village.", blacksmith, villageCenter, Direction::EAST, false, 2);
	// Village Center <-> Castle Road
	Exit* centerTocastleRoad = new Exit("north", "A wide dirt road leads toward the looming shape of the castle.", villageCenter, castleRoad, Direction::NORTH, false, 3);
	Exit* castleRoadToCenter = new Exit("south", "The path leads back to the center of the village.", castleRoad, villageCenter, Direction::SOUTH, false, 3);
	// Forest <-> Graveyard
	Exit* forestToGraveyard = new Exit("east", "A rusted gate bars your way into the graveyard.", forest, graveyard, Direction::EAST, true, 4); // locked id 4
	Exit* graveyardToForest = new Exit("west", "The only exit is the rusted gate you entered through.", graveyard, forest, Direction::WEST, false, 4);
	// Forest <-> Gravekeeper's House
	Exit* forestToGravekeeper = new Exit("south", "A worn trail descends into a shadowed glade.", forest, gravekeeperHouse, Direction::SOUTH, false, 5);
	Exit* gravekeeperToForest = new Exit("north", "A steep path leads back to the forest above.", gravekeeperHouse, forest, Direction::NORTH, false, 5);
	// Castle Road <-> Alchemist Lab
	Exit* castleRoadToAlch = new Exit("west", "A narrow side path leads to a ruined stone building.", castleRoad, alchemistLab, Direction::WEST, false, 6);
	Exit* alchToCastleRoad = new Exit("east", "A collapsed stone corridor leads back toward the castle path.", alchemistLab, castleRoad, Direction::EAST, false, 6);
	// Castle Road <-> Castle Hall
	Exit* castleRoadToCH = new Exit("north", "An ancient stone door marks the entrance — it can only be opened with a special key.", castleRoad, castleHall, Direction::NORTH, true, 7);
	Exit* CHToCastleRoad = new Exit("south", "An ancient stone door marks the exit.", castleHall, castleRoad, Direction::SOUTH, false, 7);

	// LINK EXITS
	// Safe House <-> Village Center
	safeHouse->addExit(houseDoorN);
	villageCenter->addExit(houseDoorS);
	// Village Center <-> Forest
	villageCenter->addExit(centerToForest);
	forest->addExit(forestToCenter);
	// Village Center <-> Blacksmith Workshop
	villageCenter->addExit(centerToBlacksmith);
	blacksmith->addExit(blacksmithToCenter);
	// Village Center <-> Castle Road
	villageCenter->addExit(centerTocastleRoad);
	castleRoad->addExit(castleRoadToCenter);
	// Forest <-> Graveyard
	forest->addExit(forestToGraveyard);
	graveyard->addExit(graveyardToForest);
	// Forest <-> Gravekeeper's House
	forest->addExit(forestToGravekeeper);
	gravekeeperHouse->addExit(gravekeeperToForest);
	// Castle Road <-> Alchemist Lab
	castleRoad->addExit(castleRoadToAlch);
	alchemistLab->addExit(alchToCastleRoad);
	// Castle Road <-> Castle Hall
	castleRoad->addExit(castleRoadToCH);
	castleHall->addExit(CHToCastleRoad);

	// ADD ROOMS
	addEntity(safeHouse);
	addEntity(villageCenter);
	addEntity(forest);
	addEntity(graveyard);
	addEntity(blacksmith);
	addEntity(castleRoad);
	addEntity(castleHall);
	addEntity(gravekeeperHouse);
	addEntity(alchemistLab);

	// ADD EXITS
	addEntity(houseDoorN);
	addEntity(houseDoorS);
	addEntity(centerToForest);
	addEntity(forestToCenter);
	addEntity(centerToBlacksmith);
	addEntity(blacksmithToCenter);
	addEntity(centerTocastleRoad);
	addEntity(castleRoadToCenter);
	addEntity(forestToGraveyard);
	addEntity(graveyardToForest);
	addEntity(forestToGravekeeper);
	addEntity(gravekeeperToForest);
	addEntity(castleRoadToAlch);
	addEntity(alchToCastleRoad);
	addEntity(castleRoadToCH);
	addEntity(CHToCastleRoad);


	/*NPC* gosho = new NPC("hooded figure", "", "Thank godness you're alive!");
	Enemy* orc = new Enemy("orc", "", 50, 150);

	orc->setLevel(5);
	orc->setXPYield(150);
	addEntity(gosho);
	addEntity(orc);

	Potion* hp = new Potion("vial", "", "HP", 0);
	Potion* atk = new Potion("atk", "", "AttackPower", 20);
	Potion* stam = new Potion("stam", "", "Stamina", 10);
	Weapon* sword = new Weapon("sword", "", 50, 1);
	Weapon* axe = new Weapon("axe", "", 70, 2);
	Armor* helmet = new Armor("helmet", "", 110, 1);
	Armor* bracers = new Armor("bracers", "", 75, 2);

	addEntity(hp);
	addEntity(atk);
	addEntity(stam);
	addEntity(sword);
	addEntity(helmet);
	addEntity(axe);
	addEntity(bracers);
	orc->add(axe);

	Room* room = new Room("Entrance", "This is an open field");
	Room* room2 = new Room("Hallway", "Second room");
	addEntity(room);
	addEntity(room2);

	Exit* northExit = new Exit("North Door", "", room, room2, Direction::NORTH, true, 2);
	Exit* southExit = new Exit("South Door", "", room2, room, Direction::SOUTH, false, 2);
	addEntity(northExit);
	addEntity(southExit);

	Chest* chest = new Chest("strongbox", "", true, 1);
	Key* key = new Key("strongkey", "", 2);
	Key* key1 = new Key("key", "", 1);
	addEntity(chest);
	addEntity(key);
	addEntity(key1);

	room->add(gosho);
	room->add(hp);
	room->add(atk);
	room->add(stam);
	chest->add(sword);
	chest->add(helmet);
	chest->add(bracers);
	room->add(chest);
	room->add(key);
	room->add(key1);
	room->addExit(northExit);
	room2->addExit(southExit);
	room->add(orc);*/

	player = new Player();
	player->setCurrentRoom(safeHouse);
	addEntity(player);

}

void World::showIntro() {
	cout << "=============================================================\n";

	cout << "After a great battle, your body was mistaken for dead\n";
	cout << "and taken away by skeletal hands.\n\n";

	cout << "They carried you toward an abandoned village - a place cloaked\n";
	cout << "in silence and rot - where a hidden necromancer is raising an\n";
	cout << "army of the fallen.\n\n";

	cout << "But fate intervened.\n";
	cout << "A brave villager rescued you and brought you to safety.\n";
	cout << "Now, weak and unequipped, you awaken to a dying world in need\n";
	cout << "of a hero.\n\n";

	cout << "Will you rise again and stop the darkness?\n\n";
	cout << "=============================================================\n";
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
	else if (command == "open") {
		string itemName = getCommandArgs(iss);
		player->open(itemName);
	}
	else if (command == "unlock") {
		string toUnlock = getCommandArgs(iss);
		player->unlock(toUnlock);
	}
	else if (command == "lock") {
		string toLock = getCommandArgs(iss);
		player->lock(toLock);
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
