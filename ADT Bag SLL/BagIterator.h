#include "Bag.h"

class BagIterator
{
	friend class Bag;
	
private:
	const Bag& bag;
	Node* currentElement;
	int currentFrequency;

	BagIterator(const Bag& c);
public:
	// moves the iterator to the beginning of the bag
	void first();
	
	// moves the iterator to the next element
	void next();
	
	// gets the current element from the iterator
	TElem getCurrent() const;
	
	// checks if iterator is valid
	bool valid() const;
};
