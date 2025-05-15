#include "NPC.h"

NPC::NPC(const string& name, const string& description, const string& dialogue) :
	Creature(CreatureTypes::FRIENDLY, name, description),
	dialogue(dialogue) { }

NPC::~NPC() {}

const string& NPC::getDialogue() const { return this->dialogue; }