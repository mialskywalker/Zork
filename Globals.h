#ifndef __GLOBALS__
#define __GLOBALS__

enum class Direction {
	EAST,
	WEST,
	NORTH,
	SOUTH
};

enum class Type {
	CREATURE,
	EXIT,
	ROOM,
	ITEM,
};

enum class ItemTypes {
	POTION,
	ARMOR,
	WEAPON,
	CHEST,
	KEY,
	BASE
};

enum class CreatureTypes {
	FRIENDLY,
	ENEMY,
	PLAYER
};

#endif