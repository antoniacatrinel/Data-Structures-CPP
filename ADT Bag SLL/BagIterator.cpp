#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

// complexity
// Best Case = Average Case = Worst Case = theta(1) 
BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->currentElement = this->bag.head;
	this->currentFrequency = 1;
}

// complexity
// Best Case = Average Case = Worst Case = theta(1) 
void BagIterator::first() {
	this->currentElement = this->bag.head;
}

// complexity
// Best Case = Average Case = Worst Case = theta(1) 
void BagIterator::next() {
	if (this->currentElement == nullptr)
		throw exception();

	this->currentFrequency++;
	if (this->currentFrequency > this->currentElement->info.second) // move onto next element if we finished with current element
	{
		this->currentElement = this->currentElement->next;
		this->currentFrequency = 1;
	}
}

// complexity
// Best Case = Average Case = Worst Case = theta(1) 
bool BagIterator::valid() const {
	if (this->currentElement != nullptr)
		return true;
	return false;
}

// complexity
// Best Case = Average Case = Worst Case = theta(1) 
TElem BagIterator::getCurrent() const
{
	if (this->currentElement == nullptr)
		throw exception();
	return this->currentElement->info.first;
}
