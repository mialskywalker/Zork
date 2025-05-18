#ifndef __ROOM__
#define __ROOM__

#include "Entity.h"

class Room : public Entity {
public:
	Room(const string& name, const string& description);
	~Room() override;

	// adds an exit to the room which links it to another room
	void addExit(Entity* exit);

};

#endif