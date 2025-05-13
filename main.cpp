#include <iostream>
#include "Room.h"
#include "Exit.h"

int main() {

	Entity* e = new Entity(Type::CREATURE, "Example", "Some Description");
	Room* room = new Room("Entrance", "Intro room");
	Room* room2 = new Room("Hallway", "Second room");


	Exit* northExit = new Exit("North Door", "Exit", room, room2, Direction::NORTH);
	Exit* southExit = new Exit("South Door", "Exit", room2, room, Direction::SOUTH);

	
	room->add(e);
	room->addExit(northExit);
	room2->addExit(southExit);

	room->listEntities();
	room2->listEntities();
	
	delete room2;
	delete room;

	return 0;
}