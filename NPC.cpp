#include "NPC.h"

NPC::NPC(const string& name, const string& description, const string& dialogue) :
	Creature(name, description),
	dialogue(dialogue) { }

NPC::~NPC() {}

const string& NPC::getDialogue() const { return this->dialogue; }