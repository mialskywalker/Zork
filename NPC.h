#ifndef __NPC__
#define __NPC__

#include "Creature.h"

class NPC : public Creature {
	string dialogue;

public:
	NPC(const string& name, const string& description, const string& dialogue);
	~NPC() override;
	NPC(const NPC&) = delete;
	NPC& operator=(const NPC&) = delete;
	NPC(NPC&&) = default;
	NPC& operator=(NPC&&) = default;

	const string& getDialogue() const;

};

#endif