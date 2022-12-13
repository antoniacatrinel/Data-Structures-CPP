#pragma once
#include "SortedSet.h"

class SortedSet;

class SortedSetIterator {
	friend class SortedSet;

private:
	SortedSetIterator(const SortedSet& s);

	const SortedSet& s; // reference to the container it iterates over
	int currentElement;
	DLLA arr;
	
public:
	// sets the iterator to the first element of the container
	void first();

	// moves the iterator to the previous element
	// throws exception if the iterator is not valid
	void previous();

	// moves the iterator to the next element
	// throws exception if the iterator is not valid
	void next();

	//checks if the iterator is valid
	bool valid() const;

	// returns the value of the current element from the iterator
	// throws exception if the iterator is not valid
	TElem getCurrent() const;
};
