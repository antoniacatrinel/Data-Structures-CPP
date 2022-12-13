#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	int current;
	SortedBagIterator(const SortedBag& b);

public:
	// returns the current element from the iterator
	TComp getCurrent();

	// checks if the iterator is valid
	bool valid();

	// moves the iterator to next element
	void next();

	// resets the iterator to the first position in the bag
	void first();
};
