#include <iostream>
#include "World.h"
#include "Room.h"
#include "Exit.h"
#include "Player.h"
#include "NPC.h"
#include "Potion.h"
#include "Weapon.h"
#include "Armor.h"
#include "Enemy.h"
#include "Chest.h"
#include "Key.h"

World::World() {
	isRunning = true;
	setUpWorld();
}

World::~World() {
	for (Entity* e : entities)
		delete e;
	entities.clear();
}

void World::addEntity(Entity* entity) {
	entities.push_back(entity);
}

void World::removeEntity(Entity* entity) {
	if (entities.size()) {
		for (int i = 0; i < entities.size(); i++) {
			if (entities[i] == entity) {
				entities.erase(entities.begin() + i);
				delete entity;
				break;
			}
		}
	}
}

void World::run() {
	cout << "Welcome to the world of adventure!" << endl;
	cout << "Press Enter to begin your journey, or type 'skip' to jump ahead" << endl;
	cout << ">> ";
	string input;
	getline(cin, input);
	if (input != "skip")
		showIntro();

	while (isRunning) {
		if (!player->isAlive())
			break;
		cout << endl << ">> ";
		getline(cin, input);
		processCommand(input);
	}
}

void World::setUpWorld() {


	// ROOMS
	Room* safeHouse = new Room("Safe House", "A quiet stone shelter, dimly lit by a flickering lantern. Dust hangs in the air. A lone villager watches over you.");
	Room* villageCenter = new Room("Village Center", "Cracked cobblestone paths split in four directions. The village is eerily quiet, with signs of recent struggle.");
	Room* forest = new Room("Forest", "Twisted trees and thick underbrush surround you. The wind howls unnaturally through the branches.");
	Room* graveyard = new Room("Graveyard", "Cracked gravestones and open coffins litter the cursed ground. A chill seeps into your bones.");
	Room* blacksmith = new Room("Blacksmith Workshop", "The forge glows faintly. Tools lie scattered across the floor, and something lurks in the back.");
	Room* castleRoad = new Room("Castle Road", "The path here is lined with fallen banners and cracked statues. The castle looms in the distance.");
	Room* castleHall = new Room("Castle Hall", "Tall stone columns line the grand hall. At its center stands the necromancer, cloaked in shadows.");
	Room* gravekeeperHouse = new Room("Gravekeeper's House", "The smell of decay clings to the air. Ritual tools and bones are scattered across the floor.");
	Room* alchemistLab = new Room("Alchemist Lab", "Broken shelves and smashed vials litter the floor. A few intact potions remain on a glowing table.");

	// EXITS
	// Safe House <-> Village Center
	Exit* houseDoorN = new Exit("north", "A reinforced wooden door leads to the outside world.", safeHouse, villageCenter, Direction::NORTH, false, 0);
	Exit* houseDoorS = new Exit("south", "Door to the Safe House", villageCenter, safeHouse, Direction::SOUTH, false, 0);
	// Village Center <-> Forest
	Exit* centerToForest = new Exit("east", "A narrow, overgrown path leads into the dark trees.", villageCenter, forest, Direction::EAST, false, 1);
	Exit* forestToCenter = new Exit("west", "The overgrown trail leads back to the village square.", forest, villageCenter, Direction::WEST, false, 1);
	// Village Center <-> Blacksmith Workshop
	Exit* centerToBlacksmith = new Exit("west", "You hear faint metal clanging from behind thick wooden shutters.", villageCenter, blacksmith, Direction::WEST, false, 2);
	Exit* blacksmithToCenter = new Exit("east", "The metal-reinforced door leads back to the village.", blacksmith, villageCenter, Direction::EAST, false, 2);
	// Village Center <-> Castle Road
	Exit* centerTocastleRoad = new Exit("north", "A wide dirt road leads toward the looming shape of the castle.", villageCenter, castleRoad, Direction::NORTH, false, 3);
	Exit* castleRoadToCenter = new Exit("south", "The path leads back to the center of the village.", castleRoad, villageCenter, Direction::SOUTH, false, 3);
	// Forest <-> Graveyard
	Exit* forestToGraveyard = new Exit("east", "A rusted gate bars your way into the graveyard.", forest, graveyard, Direction::EAST, true, 4); // locked id 4
	Exit* graveyardToForest = new Exit("west", "The only exit is the rusted gate you entered through.", graveyard, forest, Direction::WEST, false, 4);
	// Forest <-> Gravekeeper's House
	Exit* forestToGravekeeper = new Exit("south", "A worn trail descends into a shadowed glade.", forest, gravekeeperHouse, Direction::SOUTH, false, 5);
	Exit* gravekeeperToForest = new Exit("north", "A steep path leads back to the forest above.", gravekeeperHouse, forest, Direction::NORTH, false, 5);
	// Castle Road <-> Alchemist Lab
	Exit* castleRoadToAlch = new Exit("west", "A narrow side path leads to a ruined stone building.", castleRoad, alchemistLab, Direction::WEST, false, 6);
	Exit* alchToCastleRoad = new Exit("east", "A collapsed stone corridor leads back toward the castle path.", alchemistLab, castleRoad, Direction::EAST, false, 6);
	// Castle Road <-> Castle Hall
	Exit* castleRoadToCH = new Exit("north", "An ancient stone door marks the entrance — it can only be opened with a special key.", castleRoad, castleHall, Direction::NORTH, true, 7); // locked id 7
	Exit* CHToCastleRoad = new Exit("south", "An ancient stone door marks the exit.", castleHall, castleRoad, Direction::SOUTH, false, 7);

	// LINK EXITS
	// Safe House <-> Village Center
	safeHouse->addExit(houseDoorN);
	villageCenter->addExit(houseDoorS);
	// Village Center <-> Forest
	villageCenter->addExit(centerToForest);
	forest->addExit(forestToCenter);
	// Village Center <-> Blacksmith Workshop
	villageCenter->addExit(centerToBlacksmith);
	blacksmith->addExit(blacksmithToCenter);
	// Village Center <-> Castle Road
	villageCenter->addExit(centerTocastleRoad);
	castleRoad->addExit(castleRoadToCenter);
	// Forest <-> Graveyard
	forest->addExit(forestToGraveyard);
	graveyard->addExit(graveyardToForest);
	// Forest <-> Gravekeeper's House
	forest->addExit(forestToGravekeeper);
	gravekeeperHouse->addExit(gravekeeperToForest);
	// Castle Road <-> Alchemist Lab
	castleRoad->addExit(castleRoadToAlch);
	alchemistLab->addExit(alchToCastleRoad);
	// Castle Road <-> Castle Hall
	castleRoad->addExit(castleRoadToCH);
	castleHall->addExit(CHToCastleRoad);

	// ADD ROOMS
	addEntity(safeHouse);
	addEntity(villageCenter);
	addEntity(forest);
	addEntity(graveyard);
	addEntity(blacksmith);
	addEntity(castleRoad);
	addEntity(castleHall);
	addEntity(gravekeeperHouse);
	addEntity(alchemistLab);

	// ADD EXITS
	addEntity(houseDoorN);
	addEntity(houseDoorS);
	addEntity(centerToForest);
	addEntity(forestToCenter);
	addEntity(centerToBlacksmith);
	addEntity(blacksmithToCenter);
	addEntity(centerTocastleRoad);
	addEntity(castleRoadToCenter);
	addEntity(forestToGraveyard);
	addEntity(graveyardToForest);
	addEntity(forestToGravekeeper);
	addEntity(gravekeeperToForest);
	addEntity(castleRoadToAlch);
	addEntity(alchToCastleRoad);
	addEntity(castleRoadToCH);
	addEntity(CHToCastleRoad);

	// NPCS
	NPC* villager = new NPC("villager", "The Villager", "You're awake. I wasn't sure you'd make it.\nThey were dragging your body to the necromancer's stronghold. Take what's in the chest\nYou'll need it if you want to survive.");
	NPC* townSurvivor = new NPC("survivor", "Town Survivor", "The forest holds monsters now, but also strength.\nIf you're not ready for the castle, check the blacksmith or the lab.");
	NPC* alchemist = new NPC("alchemist", "Wounded Alchemist", "You’ll need potions. The lab has some left… if you can get past the rubble.");

	// ADD NPCS
	safeHouse->add(villager);
	villageCenter->add(townSurvivor);
	castleRoad->add(alchemist);

	// ENEMIES
	Enemy* skeleton = new Enemy("skeleton", "Rusted armor rattles as this undead patrols the area.", 50, 5, 100);
	Enemy* skeleton1 = new Enemy("skeleton", "A reanimated corpse of a fallen warrior, its bones held together by dark magic.", 50, 5, 100);
	Enemy* skeleton2 = new Enemy("skeleton", "Rusted armor rattles as this undead patrols the area.", 50, 5, 100);
	Enemy* skeleton3 = new Enemy("skeleton", "A reanimated corpse of a fallen warrior, its bones held together by dark magic.", 50, 5, 100);
	Enemy* skeleton4 = new Enemy("skeleton", "Rusted armor rattles as this undead patrols the area.", 50, 5, 100);

	Enemy* gravekeeper = new Enemy("gravekeeper", "Once a humble caretaker of the dead, now twisted by necromancy.\nHis eyes burn with loyalty to the cursed one he buried.", 100, 15, 200);
	Enemy* kingOfOld = new Enemy("king of old", "A long-dead monarch, awakened to guard the graveyard with relentless wrath.\nHis rusted crown is fused to his skull, and a cursed sword rests in his grasp.", 150, 20, 200);
	Enemy* corruptedBlacksmith = new Enemy("blacksmith", "Once a master of steel, now a puppet of dark forces.\nHis hammer drips with blood, and his forge burns with unnatural flame.", 75, 10, 150);
	Enemy* necromancer = new Enemy("necromancer", "The architect of the dead’s return. Cloaked in shadow, he commands the grave with whispers and raises armies with a single word.", 250, 25, 500);

	// Set Enemy Level and XP
	

	// ADD ENEMIES
	forest->add(skeleton);
	graveyard->add(skeleton1);
	blacksmith->add(skeleton2);
	castleRoad->add(skeleton3);
	alchemistLab->add(skeleton4);
	blacksmith->add(corruptedBlacksmith);
	gravekeeperHouse->add(gravekeeper);
	graveyard->add(kingOfOld);
	castleHall->add(necromancer);

	addEntity(skeleton);
	addEntity(skeleton1);
	addEntity(skeleton2);
	addEntity(skeleton3);
	addEntity(skeleton4);
	addEntity(gravekeeper);
	addEntity(kingOfOld);
	addEntity(corruptedBlacksmith);
	addEntity(necromancer);


	// ITEMS
	Chest* chest = new Chest("chest", "A wooden chest.", false, 8);
	Chest* blacksmithChest = new Chest("chest", "Blacksmith Chest", true, 9); // locked id 9 key dropped from corruptedBlacksmith
	Weapon* woodenSword = new Weapon("wooden sword", "Wooden Sword", 5, 1);
	Weapon* steelSword = new Weapon("steel sword", "Steel Sword", 10, 2);
	Weapon* legendarySword = new Weapon("sword of destiny", "Sword of Destiny", 25, 5);
	Armor* woodenArmor = new Armor("wooden armor", "Wooden Armor", 5, 1);
	Armor* steelArmor = new Armor("steel armor", "Steel Armor", 10, 2);
	Armor* mithrilArmor = new Armor("mithril armor", "Mithril Armor", 25, 5);
	Potion* staminaPotion = new Potion("stamina potion", "Stamina Potion", "Stamina", 10);
	Potion* healthPotion = new Potion("health potion", "Health Potion", "HP", 0);
	Potion* apPotion = new Potion("strength potion", "Strength Potion", "AttackPower", 10);
	Key* blacksmithKey = new Key("chest key", "Blacksmith Chest Key", 9);
	Key* graveyardKey = new Key("graveyard key", "Graveyard Key", 4);
	Key* castleHallKey = new Key("castle gate key", "Castle Gate Key", 7);

	chest->add(woodenSword);
	safeHouse->add(chest);

	blacksmithChest->add(steelSword);
	blacksmithChest->add(mithrilArmor);

	skeleton->add(woodenArmor);
	skeleton2->add(healthPotion);
	skeleton3->add(steelArmor);
	corruptedBlacksmith->add(blacksmithKey);
	gravekeeper->add(graveyardKey);
	kingOfOld->add(legendarySword);
	kingOfOld->add(castleHallKey);

	alchemistLab->add(apPotion);
	alchemistLab->add(staminaPotion);


	addEntity(chest);
	addEntity(blacksmithChest);
	addEntity(woodenSword);
	addEntity(steelSword);
	addEntity(legendarySword);
	addEntity(woodenArmor);
	addEntity(steelArmor);
	addEntity(mithrilArmor);
	addEntity(staminaPotion);
	addEntity(healthPotion);
	addEntity(apPotion);
	addEntity(blacksmithKey);
	addEntity(graveyardKey);
	addEntity(castleHallKey);

	blacksmith->add(blacksmithChest);

	player = new Player();
	player->setCurrentRoom(safeHouse);
	addEntity(player);

}

void World::showIntro() {
	cout << "=============================================================\n";

	cout << "After a great battle, your body was mistaken for dead\n";
	cout << "and taken away by skeletal hands.\n\n";

	cout << "They carried you toward an abandoned village - a place cloaked\n";
	cout << "in silence and rot - where a hidden necromancer is raising an\n";
	cout << "army of the fallen.\n\n";

	cout << "But fate intervened.\n";
	cout << "A brave villager rescued you and brought you to safety.\n";
	cout << "Now, weak and unequipped, you awaken to a dying world in need\n";
	cout << "of a hero.\n\n";

	cout << "Will you rise again and stop the darkness?\n\n";
	cout << "=============================================================\n";
}

string World::getCommandArgs(istringstream& iss) {
	bool bFirst = true;
	string res = "";
	string arg;
	while (iss >> arg) {
		if (bFirst) {
			res += arg;
			bFirst = false;
		}
		else {
			res += ' ' + arg;
		}
	}
	return res;
}

void World::processCommand(const string& input) {
	istringstream iss(input);
	string command, arg;
	iss >> command;

	if (command == "look") {
		cout << "You are in: " << player->getRoom()->getName() << endl;
		cout << player->getRoom()->getDescription() << endl;
		cout << "You see:" << endl;
		player->getRoom()->listEntities();
	}
	else if (command == "go") {
		iss >> arg;
		
		if (arg == "east") {
			player->move(Direction::EAST);
		}
		else if (arg == "west") {
			player->move(Direction::WEST);
		}
		else if (arg == "north") {
			player->move(Direction::NORTH);
		}
		else if (arg == "south") {
			player->move(Direction::SOUTH);
		}
		else {
			cout << "You can't go that way!" << endl;
		}
	}
	else if (command == "inventory") {
		player->listInventory();
	}
	else if (command == "talk") {
		string npcName = getCommandArgs(iss);
		bool isValidNPC = false;
		for (const auto& e : player->getRoom()->getContains()) {
			if (auto npc = dynamic_cast<NPC*>(e)) {
				if (npc->getName() == npcName)
				{
					isValidNPC = true;
					cout << npc->getDescription() << ": " << npc->getDialogue() << endl;
				}
			}
		}
		if (!isValidNPC)
			cout << npcName << " is not currently here." << endl;
	}
	else if (command == "take") {
		string itemName = getCommandArgs(iss);
		player->take(itemName);
	}
	else if (command == "drop") {
		string itemName = getCommandArgs(iss);
		player->drop(itemName);
	}
	else if (command == "use") {
		string itemName = getCommandArgs(iss);
		player->use(itemName);
	}
	else if (command == "equip") {
		string itemName = getCommandArgs(iss);
		player->equip(itemName);
	}
	else if (command == "unequip") {
		string itemName = getCommandArgs(iss);
		player->unequip(itemName);
	}
	else if (command == "open") {
		string itemName = getCommandArgs(iss);
		player->open(itemName);
	}
	else if (command == "unlock") {
		string toUnlock = getCommandArgs(iss);
		player->unlock(toUnlock);
	}
	else if (command == "lock") {
		string toLock = getCommandArgs(iss);
		player->lock(toLock);
	}
	else if (command == "status") {
		player->showStatus();
	}
	else if (command == "attack") {
		string enemyName = getCommandArgs(iss);
		player->attack(enemyName);
	}
	else if (command == "quit") {
		isRunning = false;
		cout << "Thank you for playing! See you soon!" << endl;
	}
	else {
		cout << "Invalid command!" << endl;
	}
}
