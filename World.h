#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include <sstream>

using namespace std;

class Entity;
class Player;
class Enemy;

class World {
	vector<Entity*> entities;
	bool isRunning;
	Player* player;
	Enemy* necromancer;

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

	void showIntro();

	void showCongratulations();

	void processCommand(const string& input);

	string getCommandArgs(istringstream& iss);

};

#endif