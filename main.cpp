#include <iostream>
#include "Entity.h"

int main() {

	Entity* e = new Entity(CREATURE, "Example", "Some Description");
	
	cout << e->getName() << endl << e->getDescription() << endl << e->getContains().size() << endl;

	delete e;

	return 0;
}