#include "Exit.h"

Exit::Exit(const string& name, const string& description, Room* source, Room* destination, Direction direction) :
	Entity(Type::EXIT, name, description),
	source(source),
	destination(destination),
	direction(direction) { }

Exit::~Exit() { }

Room* Exit::getSource() const { return this->source; }

Room* Exit::getDestination() const { return this->destination; }

const Direction& Exit::getDirection() const { return this->direction; }
