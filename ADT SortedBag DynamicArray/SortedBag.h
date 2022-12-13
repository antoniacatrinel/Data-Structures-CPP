#pragma once

typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;

private:
	TComp* elements;
	int nrElements;
	int capacity;
	Relation relation;

	void resize();

public:
	// constructor
	SortedBag(Relation r);

	// adds an element to the sorted bag
	void add(TComp e);

	// removes one occurence of an element from a sorted bag
	// returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	// checks if an element appearch is the sorted bag
	bool search(TComp e) const;

	// returns the number of occurrences of an element in the sorted bag
	int nrOccurrences(TComp e) const;

	// adds nr of occurences of elem into the sorted bag; if elem was not in bag, it will be added
	// throws exception if nr is negative
	void addOccurrences(int nr, TComp elem);

	// returns the number of elements from the sorted bag
	int size() const;

	// returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	// checks if the sorted bag is empty
	bool isEmpty() const;

	// destructor
	~SortedBag();
};
