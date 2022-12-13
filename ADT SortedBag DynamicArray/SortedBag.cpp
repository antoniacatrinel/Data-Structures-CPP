#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <cstddef>
#include <exception>
#include <stdio.h>
using namespace std;


// complexity
// Best Case = Average Case = Worst Case = theta(1)
// overall complexity = theta(1)
SortedBag::SortedBag(Relation r) {
	this->capacity = 1;
	this->nrElements = 0;
	this->relation = r;
	this->elements = new TComp[this->capacity];
}


// inserts the element on the correct position, so as to elements to remain ordered
// complexity
// Best Case = theta(1) -> bag is empty || element must be added on last position
// Average Case = theta(nrElements)-> element isn't already in the bag and has to be added on a random position
// Worst Case = theta(nrElements)-> element isn't already in the bag and has to be added on the first position
// overall complexity = O(nrElements)
void SortedBag::add(TComp e) {
	if (this->capacity == this->nrElements)
		resize();

	if (isEmpty() == true)   // if bag is empty, simply add the element on the first position
	{
		this->elements[0] = e;
		this->nrElements++;
		return;
	}

	int index = this->nrElements - 1;
	while (index >= 0 && this->relation(this->elements[index], e) == false)
	{
		this->elements[index + 1] = this->elements[index];
		index--;
	}
	this->elements[index + 1] = e;
	this->nrElements++;
}


// removes an occurence of an element
// complexity
// Best Case = theta(1) -> element is in the middle in the bag 
// Average Case = O(nrElements) -> element is in bag on a random poisiton / doesnt appear: theta(log2 n)
// Worst Case = theta(nrElements) -> element is on last position
// overall complexity = O(nrElements)
bool SortedBag::remove(TComp e) {
	if (search(e) == false)  // element cannot be removed because it does not exist in the bag
		return false;
	int index = 0;
	bool found = false;
	while (index < this->nrElements && found == false)
	{
		if (this->elements[index] == e)
			found = true;
		else
			index++; // only increase if we didnt find
	}
	if (found == false)
		return false;
	else // remove
	{
		for (int i = index; i < this->nrElements - 1; i++)
			this->elements[i] = this->elements[i + 1];
		this->nrElements--;
		return true;
	}
}


// binary search algorithm for searching an element in the sorted bag
// complexity
// Best Case = theta(1) -> searched element is in the middle
// Average Case = theta(log2 n) -> searched element can be anywhere between fisrt and last element, except in the middle
// Worst Case = theta(log2 n) -> searched element is on the first or last position
// overall complexity = O(log2 n)
// space complexity = theta(1)
bool SortedBag::search(TComp elem) const {
	int left = 0;
	int right = this->nrElements - 1;
	int middle;

	while (left <= right)
	{
		middle = (left + right) / 2;
		if (this->elements[middle] == elem)
			return true;
		if (this->relation(this->elements[middle], elem) == false)
			right = middle - 1;
		else
			left = middle + 1;
	}
	return false;
}


// complexity
// Best Case = theta(log2 n)
// Average Case = theta(log2 n) 
// Worst Case = theta(log2 n) 
// overall complexity = O(log2 n)
int SortedBag::nrOccurrences(TComp elem) const {
	int left = 0, right = this->nrElements - 1, middle;
	// binary search of the start index of searched element
	int startIndex = -1;
	while (left <= right)
	{
		middle = (left + right) / 2;
		if (this->relation(this->elements[middle], elem) == false)
			right = middle - 1;
		else
			if (this->elements[middle] == elem)
			{
				startIndex = middle;
				right = middle - 1;
			}
			else
				left = middle + 1;
	}

	if (startIndex == -1)
		return 0;
	// binary search of the end index of searched element
	int endIndex = -1;
	left = 0;
	right = this->nrElements - 1;
	while (left <= right)
	{
		middle = (left + right) / 2;
		if (this->relation(this->elements[middle], elem) == false)
			right = middle - 1;
		else
			if (this->elements[middle] == elem)
			{
				endIndex = middle;
				left = middle + 1;
			}
			else
				left = middle + 1;
	}

	if (startIndex != -1 && endIndex != -1)
	{
		return endIndex - startIndex + 1;
	}
	return 0;
}


// complexity
// Best Case = theta(1)
// Average Case = theta(nr * nrELements)
// Worst Case = theta(nr * nrELements)
// overall complexity = O(nr * nrELements)
void SortedBag::addOccurrences(int nr, TComp elem)
{
	if (nr < 0)
		throw exception();
	else
	{
		int index = nr;
		while (index)
		{
			add(elem);
			index--;
		}
	}
}


// complexity
// Best Case = Average Case = Worst Case = theta(1)
// overall complexity = theta(1)
int SortedBag::size() const {
	return this->nrElements;
}


// complexity
// Best Case = Average Case = Worst Case = theta(1)
// overall complexity = theta(1)
bool SortedBag::isEmpty() const {
	if (this->nrElements == 0)
		return true;
	return false;
}


// complexity
// Best Case = Average Case = Worst Case = theta(1)
// overall complexity = theta(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


// complexity
// Best Case = Average Case = Worst Case = theta(1)
// overall complexity = theta(1)
SortedBag::~SortedBag() {
	delete[] this->elements;
}


// complexity
// Best Case = Average Case = Worst Case = theta(nrElements) 
// overall compexity = theta(nrElements) 
void SortedBag::resize()
{
	this->capacity *= 2;

	// allocate new memory, copy everything and deallocate the old memory
	int i;
	TComp* new_elems = new TComp[this->capacity];
	if (new_elems == NULL)   // allocation failed 
		return;
	else
	{
		for (i = 0; i < this->nrElements; i++)
			new_elems[i] = this->elements[i];
		delete[] this->elements;
		this->elements = new_elems;  // point to newly allocated memory
	}
}
