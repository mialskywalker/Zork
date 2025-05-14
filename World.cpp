#include <iostream>
#include <sstream>
#include "World.h"
#include "Room.h"
#include "Exit.h"
#include "Player.h"
#include "NPC.h"

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
		cout << endl << ">> ";
		string input;
		getline(cin, input);
		processCommand(input);
	}
}

void World::setUpWorld() {
	NPC* gosho = new NPC("Gosho", "Friendly", "Thank godness you're alive!");
	NPC* zvezdi = new NPC("Zvezdi", "Friendly", "Hello, traveller!");
	addEntity(gosho);
	addEntity(zvezdi);

	Room* room = new Room("Entrance", "Intro room");
	Room* room2 = new Room("Hallway", "Second room");
	addEntity(room);
	addEntity(room2);

	Exit* northExit = new Exit("North Door", "Exit", room, room2, Direction::NORTH);
	Exit* southExit = new Exit("South Door", "Exit", room2, room, Direction::SOUTH);
	addEntity(northExit);
	addEntity(southExit);

	room->add(gosho);
	room->addExit(northExit);
	room2->addExit(southExit);
	room2->add(zvezdi);

	player = new Player();
	player->setCurrentRoom(room);
	addEntity(player);

}

void World::processCommand(const string& input) {
	istringstream iss(input);
	string command, arg;
	iss >> command;

	if (command == "look") {
		cout << "You are in: " << player->currentRoom->getName() << endl;
		cout << "You see:" << endl;
		player->currentRoom->listEntities();
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
	else if (command == "talk") {
		iss >> arg;
		bool isValidNPC = false;
		for (const auto& e : player->currentRoom->getContains()) {
			if (auto npc = dynamic_cast<NPC*>(e)) {
				if (npc->getName() == arg)
				{
					isValidNPC = true;
					cout << npc->getName() << ": " << npc->getDialogue() << endl;
				}
			}
		}
		if (!isValidNPC)
			cout << arg << " is not currently here." << endl;
	}
	else if (command == "quit") {
		isRunning = false;
		cout << "Thank you for playing! See you soon!" << endl;
	}
	else {
		cout << "Invalid command!" << endl;
	}
}
