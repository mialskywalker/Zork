#ifndef __ROOM__
#define __ROOM__

#include "Entity.h"

class Room : public Entity {
public:
	Room(const string& name, const string& description);
	~Room() override;

	void addExit(Entity* exit);

};

#endif