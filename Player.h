#ifndef __PLAYER__
#define __PLAYER__

#include "Creature.h"
#include "Globals.h"

class Player : public Creature {
public:
	Room* currentRoom = nullptr;

	Player();

	// Getters and Setters

	const Room* getRoom() const;

	void setCurrentRoom(Room* room);

	// Methods

	void move(const Direction& direction);
};

#endif