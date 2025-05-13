#ifndef __CREATURE__
#define __CREATURE__

#include "Entity.h"

class Room;

class Creature : public Entity {
	Room* location = nullptr;
	int health;

public:
	Creature(const string& name, const string& description);
	~Creature() override;
	Creature(const Creature&) = delete;
	Creature& operator=(const Creature&) = delete;
	Creature(Creature&&) = default;
	Creature& operator=(Creature&&) = default;

	// Getters and Setters

	int getHealth() const;

	void setHealth(int amount);

	// Methods

	bool isAlive() const;
};

#endif