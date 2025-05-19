#include <iostream>
#include "World.h"

int main() {

	World world;
	world.run();

	cout << "Press Enter to exit..." << endl;
	cin.get();
	return 0;
}