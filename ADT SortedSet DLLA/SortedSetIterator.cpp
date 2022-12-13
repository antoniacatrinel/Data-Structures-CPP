#include "SortedSetIterator.h"
#include <exception>

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
SortedSetIterator::SortedSetIterator(const SortedSet& s) :s(s) {
	this->arr = s.dlla;
	this->currentElement = s.dlla.head;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
void SortedSetIterator::first()
{
	this->currentElement = s.dlla.head;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
void SortedSetIterator::previous()
{
	if (!this->valid()) 
		throw std::exception();
	else 
	{
		if (this->currentElement == s.dlla.head) 
			this->currentElement = -1;
		
		else 
			this->currentElement = this->arr.nodes[this->currentElement].prev;
		
	}
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
void SortedSetIterator::next()
{
	if (!this->valid())
		throw std::exception();
	
	this->currentElement = this->arr.nodes[this->currentElement].next;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
bool SortedSetIterator::valid() const
{
	return this->currentElement != -1;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
TElem SortedSetIterator::getCurrent() const
{
	if (!this->valid())
		throw std::exception();

	return this->arr.nodes[this->currentElement].info;
}
