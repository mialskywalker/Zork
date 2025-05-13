#ifndef __ROOM__
#define __ROOM__

#include "Entity.h"

class Room : public Entity {
public:
	Room(const string& name, const string& description);
	~Room() override;
	Room(const Room&) = delete;
	Room& operator=(const Room&) = delete;
	Room(Room&&) = default;
	Room& operator=(Room&&) = default;

	void addExit(Entity* exit);

};

#endif