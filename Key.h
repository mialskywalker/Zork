#ifndef __KEY__
#define __KEY__

#include "Item.h"

class Key : public Item {
	int id;
public:
	Key(const string& name, const string& description, int id);
	~Key() override;
	Key(const Key&) = delete;
	Key& operator=(const Key&) = delete;
	Key(Key&&) = default;
	Key& operator=(Key&&) = default;

	int getId() const;
};

#endif