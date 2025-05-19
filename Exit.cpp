#include <iostream>
#include "Exit.h"

Exit::Exit(const string& name, const string& description, Room* source, Room* destination, Direction direction, bool isLocked, int id) :
	Entity(Type::EXIT, name, description),
	source(source),
	destination(destination),
	direction(direction),
	isLocked(isLocked),
	id(id) { }

Exit::~Exit() { }

Room* Exit::getSource() const { return this->source; }

Room* Exit::getDestination() const { return this->destination; }

const Direction& Exit::getDirection() const { return this->direction; }

bool Exit::getIsLocked() const { return this->isLocked; }

int Exit::getId() const { return this->id; }

void Exit::unlock(int keyId) {
	if (!getIsLocked()) {
		cout << getName() << " is not locked!" << endl;
		return;
		// checks if exit is unlocked | does nothing if it is unlocked -> code below doesn't run
	}

	this->isLocked = false;
	cout << getName() << " successfully unlocked!" << endl;
	// sets locked status to false
}

void Exit::lock(int keyId) {
	if (getIsLocked()) {
		cout << getName() << " is already locked!" << endl;
		return;
		// checks if exit is locked | does nothing if it is locked -> code below doesn't run
	}

	this->isLocked = true;
	cout << getName() << " successfully locked!" << endl;
	// sets locked status to true
}
