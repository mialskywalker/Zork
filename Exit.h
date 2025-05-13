#ifndef __EXIT__
#define __EXIT__

#include "Entity.h"
#include "Globals.h"

class Room;

class Exit : public Entity {
	Direction direction;
	Room* source;
	Room* destination;

public:
	Exit(const string& name, const string& description, Room* source, Room* destination, Direction direction);
	~Exit() override;
	Exit(const Exit&) = delete;
	Exit& operator=(const Exit&) = delete;
	Exit(Exit&&) = default;
	Exit& operator=(Exit&&) = default;

	// Getters

	Room* getSource() const;

	Room* getDestination() const;

	const Direction& getDirection() const;

};

#endif