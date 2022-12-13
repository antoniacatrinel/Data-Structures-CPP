#pragma once
#include "Set.h"

class SetIterator
{
	friend class Set;
private:

	const Set& set;   // reference to the container it iterates over
	SetIterator(const Set& s);

	int currentHashKey;

public:
	// sets the iterator to the first element of the container
	void first();

	// moves the iterator to the next element
	// throws exception if the iterator is not valid
	void next();

	// returns the value of the current element from the iterator
	// throws exception if the iterator is not valid
	TElem getCurrent();

	// checks if the iterator is valid
	bool valid() const;
};


