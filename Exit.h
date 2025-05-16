#ifndef __EXIT__
#define __EXIT__

#include "Entity.h"
#include "Globals.h"

class Room;

class Exit : public Entity {
	Direction direction;
	Room* source;
	Room* destination;
	bool isLocked;
	int id;

public:
	Exit(const string& name, const string& description, Room* source, Room* destination, Direction direction, bool isLocked, int id);
	~Exit() override;

	Room* getSource() const;

	Room* getDestination() const;

	const Direction& getDirection() const;

	bool getIsLocked() const;

	int getId() const;

	void unlock(int keyId);

	void lock(int keyId);

};

#endif