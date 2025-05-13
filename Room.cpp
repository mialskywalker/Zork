#include "Room.h"

Room::Room(const string& name, const string& description) :
	Entity(Type::ROOM, name, description) { }

Room::~Room() {}

void Room::addExit(Entity* exit) {
	if (exit->getType() == Type::EXIT)
		getContains().push_back(std::move(exit));
}