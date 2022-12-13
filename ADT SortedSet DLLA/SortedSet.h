#pragma once
#define CAPACITY 10
#define NULL_TELEM -11111

typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
class SortedSetIterator;

struct Node {
	TComp info;
	int next, prev;
};

struct DLLA {
	Node* nodes;
	int capacity, size, head, tail, firstEmpty;
};

class SortedSet {
	friend class SortedSetIterator;
private:

	// Representation of the Sorted Set
	DLLA dlla;
	Relation relation;

	// allocates new memory for a new node
	int allocate();

	// frees the memory at position pos
	void free(int pos);

	// inserts given element e at position pos in DLLA
	void insertPosition(TComp e, int pos);

	// performs a resize of the DLLA
	void resize();

public:
	//constructor
	SortedSet(Relation r);

	//adds an element to the sorted set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
	//it returns false
	bool add(TComp e);

	//removes an element from the sorted set
	//if the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	//checks if an element is in the sorted set
	bool search(TElem elem) const;

	//returns the number of elements from the sorted set
	int size() const;

	//checks if the sorted set is empty
	bool isEmpty() const;

	//returns an iterator for the sorted set
	SortedSetIterator iterator() const;

	// destructor
	~SortedSet();
};
