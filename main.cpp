#include <iostream>
#include "Room.h"

int main() {

	Entity* e = new Entity(Type::CREATURE, "Example", "Some Description");
	Room* room = new Room("Entrance", "Intro room");
	
	cout << e->getName() << endl << e->getDescription() << endl << e->getContains().size() << endl;
	cout << room->getName() << endl << room->getDescription() << endl << room->getContains().size() << endl;
	
	delete room;
	delete e;

	return 0;
}