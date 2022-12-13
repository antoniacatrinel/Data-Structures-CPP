#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>
using namespace std;


// complexity
// Best Case = Average Case = Worst Case = theta(1)
// overall complexity = theta(1)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->current = 0;
}


// complexity
// Best Case = Average Case = Worst Case = theta(1)
// overall complexity = theta(1)
TComp SortedBagIterator::getCurrent() {
	if (this->current == this->bag.nrElements)
		throw exception();
	return this->bag.elements[this->current];
}


// complexity
// Best Case = Average Case = Worst Case = theta(1)
// overall complexity = theta(1)
bool SortedBagIterator::valid() {
	if (this->current < this->bag.nrElements)
		return true;
	return false;
}


// complexity
// Best Case = Average Case = Worst Case = theta(1)
// overall complexity = theta(1)
void SortedBagIterator::next() {
	if (this->current == this->bag.nrElements)
		throw exception();
	this->current++;
}


// complexity
// Best Case = Average Case = Worst Case = theta(1)
// overall complexity = theta(1)
void SortedBagIterator::first() {
	this->current = 0;
}

