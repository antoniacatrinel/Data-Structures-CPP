#include "Set.h"
#include "SetITerator.h"

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
int Set::hCode(TElem k) const
{
	return abs(int(k));
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
TElem Set::h1(TElem k) const
{
	return hCode(k) % this->capacity;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
TElem Set::h2(TElem k) const
{
	return 1 + (hCode(k) % (this->capacity - 1));
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
int Set::h(TElem k, int i) const
{
	return (h1(k) + i * h2(k)) % this->capacity;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(capacity) 
// Overall complexity = theta(capacity)
Set::Set()
{
	// prime number
	this->capacity = 53;
	this->length = 0;
	this->empty = NULL_TELEM;
	this->deleted = DELETED_TELEM;

	this->elements = new TElem[this->capacity];
	int i;

	// initialize the elements with NULL_TELEM
	for (i = 0; i < this->capacity; i++)
		this->elements[i] = this->empty;
}

// resize and rehash
// complexity 
// Best Case = Worst Case = Average Case = theta(newcapacity) 
// Overall complexity = theta(newcapacity)
void Set::resize()
{
	// modify capacity, ensure it remains prime
	int prime = firstPrimeGreaterThan(this->capacity * 2);

	// allocate new space
	TElem* newElems = new TElem[prime];

	int oldCapacity = this->capacity;
	this->capacity = prime;
	int i;

	for (i = 0; i < this->capacity; i++)
		newElems[i] = NULL_TELEM;

	// add each element from the previous table to the new table and compute the new hashfunction
	for (i = 0; i < oldCapacity; i++)
	{
		TElem current = this->elements[i];
		int index = 0; //  probe number
		int position = h(current, index);
		// search until you find a pos that has never been occupied or where the element has been deleted
		while (index < this->capacity && newElems[position] != this->empty)
		{
			if (newElems[position] == current)
				break;
			index++;
			position = h(current, index);
			// we generate multiple positions using probe number and examine if they are empty
		}
		newElems[position] = current;
	}

	delete[] this->elements;
	this->elements = newElems;   // point to newly allocated memory
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
int Set::firstPrimeGreaterThan(int x)
{
	x++;
	while (!isPrime(x))
		x++;
	return x;
}

// complexity: O(sqrt(x))
bool Set::isPrime(int x)
{
	if (x < 2 || x > 2 && x % 2 == 0)
		return false;
	for (int d = 3; d * d <= x; d += 2)
		if (x % d == 0)
			return false;
	return true;
}

// complexity 
// Best Case =  Average Case = theta(1) 
// Worst Case = theta(capacity) 
// Overall complexity = O(capacity)
bool Set::add(TElem elem) {
	if (search(elem) == true)  // elem already in set
		return false;

	if (this->length == this->capacity)
		this->resize();

	int index = 0; //  probe number
	int position = h(elem, index);

	// search until you find a pos that has never been occupied or where the element has been deleted
	while (index < this->capacity && this->elements[position] != this->empty && this->elements[position] != this->deleted)
	{
		if (this->elements[position] == elem)
			break;
		index++;
		position = h(elem, index);
		// we generate multiple positions using probe number and examine if they are empty
	}
	if (this->elements[position] == this->empty || this->elements[position] == this->deleted)
		this->length++;
	this->elements[position] = elem;
	return true;
}

// complexity 
// Best Case =  Average Case = theta(1) 
// Worst Case = theta(capacity) 
// Overall complexity = O(capacity)
bool Set::remove(TElem elem) {
	int index = 0; //  probe number
	int position = h(elem, index);
	// search until you find a pos that has never been occupied or where the element has been deleted
	while (index < this->capacity && this->elements[position] != elem && this->elements[position] != this->empty)
	{
		index++;
		position = h(elem, index);
		// we generate multiple positions using probe number and examine if they are empty
	}
	if (index == this->capacity || this->elements[position] == this->empty)
		return false;
	this->length--;
	this->elements[position] = this->deleted;
	return true;
}

// complexity 
// Best Case =  Average Case = theta(1) 
// Worst Case = theta(capacity) 
// Overall complexity = O(capacity)
// the average case is theta(1) because the load factor(length/capacity) is < 1
bool Set::search(TElem elem) const {
	int index = 0; //  probe number
	int position = h(elem, index);

	// search until you find a pos that has never been occupied or where the element has been deleted
	while (index < this->capacity && this->elements[position] != this->empty)
	{
		if (this->elements[position] == elem)
			return true;
		index++;
		position = h(elem, index);
		// we generate multiple positions using probe number and examine if they are empty
	}
	return false;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
int Set::size() const {
	return this->length;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
bool Set::isEmpty() const {
	return this->length == 0;
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
SetIterator Set::iterator() const {
	return SetIterator(*this);
}

// complexity 
// Best Case = Worst Case = Average Case = theta(1) 
// Overall complexity = theta(1)
Set::~Set() {
	delete[] this->elements;
}
