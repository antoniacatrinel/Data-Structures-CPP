#pragma once
#include <utility>

typedef int TElem;
typedef std::pair<TElem, int> TElemPair;
#define NULL_TELEM -111111;
#define NULL_TELEMPAIR std::pair<TElem, int>(-111111, -111111);

class BagIterator; 

// SLL Node structure
struct Node
{
	TElemPair info;
	Node* next;
};

class Bag {

	// representation: keep elements as pairs (element, frequency)
private:
	Node* head;
	int nrElements;

	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurrence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appears is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	// removes all occurences of given element from the bag
	int removeAllOccurences(TElem elem);

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();
};
