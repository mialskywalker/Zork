#ifndef __WORLD__
#define __WORLD__

#include <vector>

using namespace std;

class Entity;
class Player;

class World {
	vector<Entity*> entities;
	bool isRunning;
	Player* player;

public:
	World();
	~World();
	World(const World&) = delete;
	World& operator=(const Entity&) = delete;
	World(World&&) = default;
	World& operator=(World&&) = default;

	void addEntity(Entity* entity);

	void removeEntity(Entity* entity);

	void run();

	void setUpWorld();

	void processCommand(const string& input);

};

#endif