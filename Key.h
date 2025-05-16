#ifndef __KEY__
#define __KEY__

#include "Item.h"

class Key : public Item {
	int id;
public:
	Key(const string& name, const string& description, int id);
	~Key() override;

	int getId() const;
};

#endif