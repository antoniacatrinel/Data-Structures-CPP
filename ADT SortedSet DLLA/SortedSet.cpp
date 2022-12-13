#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
#include <stdlib.h>

// complexity
// Best Case = Average Case = Worst Case = theta(n) 
// Overall complexity = theta(n), where n = initial capacity
SortedSet::SortedSet(Relation r)
{
	this->dlla.capacity = CAPACITY;
	this->dlla.size = 0;
	this->relation = r;

	this->dlla.head = -1;
	this->dlla.tail = -1;
	this->dlla.firstEmpty = 0;

	this->dlla.nodes = new Node[CAPACITY];

	int i;
	for (i = 0; i < CAPACITY - 1; i++) 
		this->dlla.nodes[i].next = i + 1;
	
	this->dlla.nodes[CAPACITY - 1].next = -1;

	for (i = 1; i < CAPACITY; i++) 
		this->dlla.nodes[i].prev = i - 1;
	
	this->dlla.nodes[0].prev = -1;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
int SortedSet::allocate()
{
	int newElem = this->dlla.firstEmpty;

	if (newElem != -1)
	{
		this->dlla.nodes[this->dlla.firstEmpty].prev = -1;
		this->dlla.firstEmpty = this->dlla.nodes[this->dlla.firstEmpty].next;
		this->dlla.nodes[newElem].next = -1;
		this->dlla.nodes[newElem].prev = -1;
	}
	return newElem;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
void SortedSet::free(int pos)
{
	this->dlla.nodes[pos].next = this->dlla.firstEmpty;
	this->dlla.nodes[pos].prev = -1;
	this->dlla.nodes[this->dlla.firstEmpty].prev = pos;
	this->dlla.firstEmpty = pos;
}

// complexity
// Best Case = theta(1) 
// Worst Case = Average Case = theta(n) 
// Overall complexity = O(n)
void SortedSet::insertPosition(TComp e, int pos)
{
	int newElement = this->allocate();

	if (newElement == -1) 
	{   // allocation failed 
		this->resize();
		newElement = this->allocate();
	}

	this->dlla.nodes[newElement].info = e;

	if (pos == 0) 
	{
		if (this->dlla.head == -1)
		{
			this->dlla.head = newElement;
			this->dlla.tail = newElement;
		}
		else 
		{
			this->dlla.nodes[newElement].next = this->dlla.head;
			this->dlla.nodes[this->dlla.head].prev = newElement;
			this->dlla.head = newElement;
		}
	}
	else 
	{
		int currentNode = this->dlla.head;
		int currentPosition = 0;
		while (currentNode != -1 && currentPosition < pos - 1) 
		{
			currentNode = this->dlla.nodes[currentNode].next;
			currentPosition++;
		}

		if (currentNode != -1) 
		{
			int nextNode = this->dlla.nodes[currentNode].next;
			this->dlla.nodes[currentNode].next = newElement;
			this->dlla.nodes[newElement].next = nextNode;
			this->dlla.nodes[newElement].prev = currentNode;

			if (nextNode == -1) 
				this->dlla.tail = newElement;
			else 
				this->dlla.nodes[nextNode].prev = newElement;
		}
	}
}

// complexity 
// Best Case = Worst Case = Average Case = theta(n) 
// Overall complexity = theta(n), where n = capacity
void SortedSet::resize()
{
	Node* newElements = new Node[this->dlla.capacity * 2];

	int i;
	// copy first half of the elements
	for (i = 0; i < this->dlla.capacity; i++)
		newElements[i] = this->dlla.nodes[i];

	// initialize second half nexts nodes
	for (i = this->dlla.capacity; i < 2 * this->dlla.capacity - 1; i++)
		newElements[i].next = i + 1;

	newElements[this->dlla.capacity * 2 - 1].next = -1;

	//init the second half prevs
	for (int i = this->dlla.capacity + 1; i < 2 * this->dlla.capacity; i++)
		newElements[i].prev = i - 1;

	newElements[this->dlla.capacity].prev = -1;
	this->dlla.firstEmpty = dlla.capacity;
	this->dlla.capacity *= 2;		// double the capacity
	delete[] dlla.nodes;			// delete the old memory
	this->dlla.nodes = newElements;	// point to newly allocated memory
}

// complexity
// Best Case = theta(1) 
// Worst Case = Average Case = theta(n) 
// Overall complexity = O(n)
bool SortedSet::add(TComp e)
{
	if (this->search(e))
		return false;

	int currentElement = this->dlla.head;
	int currentPosition = 0;
	while (currentPosition < this->size() && currentElement != -1  && this->dlla.nodes[currentElement].info != e && this->relation(this->dlla.nodes[currentElement].info, e))
	{
		currentElement = this->dlla.nodes[currentElement].next;
		currentPosition++;
	}

	this->insertPosition(e, currentPosition);
	this->dlla.size++;
	return true;
}

// complexity
// Best Case = theta(1) 
// Worst Case = Average Case = theta(n) 
// Overall complexity = O(n)
bool SortedSet::remove(TComp e)
{
	int currentNode = this->dlla.head;
	int previousNode = -1;

	while (currentNode != -1 && (this->dlla.nodes[currentNode].info == e || this->relation(this->dlla.nodes[currentNode].info, e)))
	{
		if (this->dlla.nodes[currentNode].info == e) 
		{
			if (currentNode == this->dlla.head) 
				this->dlla.head = this->dlla.nodes[currentNode].next;
			
			if (currentNode == this->dlla.tail) 
				this->dlla.tail = this->dlla.nodes[currentNode].prev;
			
			if (this->dlla.nodes[currentNode].next != -1) 
				this->dlla.nodes[previousNode].next = this->dlla.nodes[currentNode].prev;
			
			if (this->dlla.nodes[currentNode].prev != -1) 
				this->dlla.nodes[previousNode].next = this->dlla.nodes[currentNode].next;
			
			this->free(currentNode);
			this->dlla.size--;
			return true;   // delete successfull
		} 

		previousNode = currentNode;
		currentNode = this->dlla.nodes[currentNode].next;
	}
	return false;
}

// complexity
// Best Case = theta(1) 
// Worst Case = Average Case = theta(n) 
// Overall complexity = O(n)
bool SortedSet::search(TElem elem) const
{
	if (this->isEmpty())
		return false;

	int currentNode = this->dlla.head;
	while (currentNode != -1 && (this->dlla.nodes[currentNode].info == elem || this->relation(this->dlla.nodes[currentNode].info, elem))) 
	{
		if (this->dlla.nodes[currentNode].info == elem)
			return true;

		currentNode = this->dlla.nodes[currentNode].next;
	}
	return false;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
int SortedSet::size() const
{
	return this->dlla.size;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
bool SortedSet::isEmpty() const
{
	return this->dlla.size == 0;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
SortedSetIterator SortedSet::iterator() const
{
	return SortedSetIterator(*this);
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
SortedSet::~SortedSet()
{
	delete[] this->dlla.nodes;
}
