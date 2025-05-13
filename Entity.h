#ifndef __ENTITY__
#define __ENTITY__

#include <string>
#include <list>
#include "Globals.h"

using namespace std;

class Entity {
	Type type;
	string name;
	string description;
	list<Entity*> contains;

public:
	Entity(const Type type, const string& name, const string& description);
	virtual ~Entity();
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;
	Entity(Entity&&) = default;
	Entity& operator=(Entity&&) = default;

	// Getters

	Type getType() const;

	const string& getName() const;

	const string& getDescription() const;

	list<Entity*>& getContains();

	// Methods

	virtual void add(Entity* entity);
	
	//virtual void destroy(Entity* entity);

	//virtual void remove(Entity* entity);

	void listEntities() const;

};

#endif