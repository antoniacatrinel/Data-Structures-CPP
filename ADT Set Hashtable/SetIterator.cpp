#include "SetIterator.h"
#include "Set.h"
#include <exception>

// complexity 
// Best Case = Worst Case = Average Case = theta(capacity) 
// Overall complexity = theta(capacity)
SetIterator::SetIterator(const Set& m) : set(m)
{
	this->currentHashKey = 0;
	// search for the first element which is not NULL
	while ((this->set.elements[this->currentHashKey] == NULL_TELEM || this->set.elements[this->currentHashKey] == DELETED_TELEM) && this->valid())
		this->currentHashKey++;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(capacity) 
// Overall complexity = theta(capacity)
void SetIterator::first() {
	this->currentHashKey = 0;

	// search for the first element which is not NULL
	while ((this->set.elements[this->currentHashKey] == NULL_TELEM || this->set.elements[this->currentHashKey] == DELETED_TELEM) && this->valid())
		this->currentHashKey++;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(capacity) 
// Overall complexity = theta(capacity)
void SetIterator::next() {
	if (!this->valid())
		throw std::exception();

	this->currentHashKey++;
	// search for the first element which is not NULL
	while ((this->set.elements[this->currentHashKey] == NULL_TELEM || this->set.elements[this->currentHashKey] == DELETED_TELEM) && this->valid())
		this->currentHashKey++;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
TElem SetIterator::getCurrent()
{
	if (!this->valid())
		throw std::exception();

	return this->set.elements[this->currentHashKey];
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
bool SetIterator::valid() const {
	return this->currentHashKey < this->set.capacity;
}
