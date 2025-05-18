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

	// add entities to the list
	void addEntity(Entity* entity);

	// removes an entity from the list
	void removeEntity(Entity* entity);

	// game loop
	void run();

	// initializes the game world: creates rooms, exits, items, npcs, enemies
	// allocates all game entities and connects them
	// must be called before the game starts
	void setUpWorld();

	// show the intro text
	void showIntro();

	// show the text at the end - when necromancer is defeated
	void showCongratulations();

	// parses and executes the player's input command
	void processCommand(const string& input);

	// extracts and returns the remainig arguments from a command input stream | Example: "take wooden sword" - returns "wooden sword"
	string getCommandArgs(istringstream& iss);

};

#endif