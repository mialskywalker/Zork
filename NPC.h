#ifndef __NPC__
#define __NPC__

#include "Creature.h"

class NPC : public Creature {
	string dialogue;

public:
	NPC(const string& name, const string& description, const string& dialogue);
	~NPC() override;

	const string& getDialogue() const;

};

#endif