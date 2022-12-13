#include "Bag.h"
#include "BagIterator.h"
#include <exception>
using namespace std;


Bag::Bag() {
	this->head = nullptr;
	this->nrElements = 0;
}

// complexity
// Best Case: theta(1) - bag is empty || element already exists on first position
// Average Case: O(nrElements)
// Worst Case: theta(nrElements) -> add on last position
// Overall complexity: O(nrElements)
void Bag::add(TElem elem) {
	Node* newNode = new Node;
	newNode->info.first = elem;
	newNode->info.second = 1;
	newNode->next = nullptr;

	// if bag is empty, add element on first position
	if (this->head == nullptr)
	{
		this->head = newNode;
		this->nrElements++;
		return;
	}

	Node* currentNode;
	currentNode = this->head;
	while (currentNode->next != nullptr)
	{
		if (currentNode->info.first == elem)
		{
			currentNode->info.second += 1;
			this->nrElements++;
			delete newNode;
			return;
		}
		currentNode = currentNode->next;
	}
	// check for last element
	if (currentNode->info.first == elem)
	{
		currentNode->info.second += 1;
		this->nrElements++;
		delete newNode;
		return;
	}

	// if element was not already in the bag
	newNode->next = currentNode->next;
	currentNode->next = newNode;
	this->nrElements++;
}

// complexity
// Best Case: theta(1) -> element is on first position
// Average Case: O(nrElements)
// Worst Case: theta(nrElements) -> element is on last position
// Overall complexity: O(nrElements) 
bool Bag::remove(TElem elem) {
	if (!search(elem))
		return false;
	
	// if head has to be deleted
	if (this->head->info.first == elem)
	{
		if (this->head->info.second > 1)  // remove one occurrence
		{
			this->head->info.second -= 1;
			this->nrElements--;
			return true;
		}
		// delete permanently
		Node* nextNode;
		nextNode = this->head->next;
		delete this->head;
		this->head = nextNode;
		this->nrElements--;
		return true;
	}
	else
	{
		Node* currentNode = this->head;
		Node* previousNode = new Node;
		while (currentNode != nullptr)
		{  
			if (currentNode->info.first == elem)
			{
				if (currentNode->info.second > 1)  // remove one occurrence
				{
					currentNode->info.second -= 1;
					this->nrElements--;
					return true;
				}
				// delete permanently
				previousNode->next = currentNode->next;
				delete currentNode;
				this->nrElements--;
				return true;
			}
			previousNode = currentNode;
			currentNode = currentNode->next;
		}
		return true;
	}
}

// complexity
// Best Case: theta(1) - element is on first position or bag is empty
// Average Case: O(nrElements)
// Worst Case: theta(nrElements) -> element is on last position
// Overall complexity: O(nrElements)
bool Bag::search(TElem elem) const {
	if (isEmpty())
		return false;

	Node* currentNode = this->head;
	while (currentNode != nullptr)
	{
		if (currentNode->info.first == elem)
			return true;
		currentNode = currentNode->next;
	}
	return false; 
}

// complexity
// Best Case: theta(1) - element is on first position or bag is empty
// Average Case: O(nrElements)
// Worst Case: theta(nrElements) -> element is on last position
// Overall complexity: O(nrElements)
int Bag::nrOccurrences(TElem elem) const {
	if (isEmpty())
		return 0;

	Node* currentNode = this->head;
	while (currentNode != nullptr)
	{
		if (currentNode->info.first == elem)
			return currentNode->info.second;
		currentNode = currentNode->next;
	}
	return 0;
}

// complexity
// Best Case: theta(1) -> element is on first position in list
// Average Case: O(nrElements)
// Worst Case: theta(nrElements) -> element is on last position
// Overall complexity: O(nrElements) 
// returns number of elements removed
int Bag::removeAllOccurences(TElem elem)
{
	if (!search(elem))
		return 0;

	// if head has to be deleted
	if (this->head->info.first == elem)
	{
		int nrOcc = this->head->info.second; // how many elements I deleted
		Node* nextNode;
		nextNode = this->head->next;
		delete this->head;
		this->head = nextNode;
		this->nrElements -= nrOcc;
		return nrOcc;
	}
	else // iterate through list 
	{
		Node* currentNode = this->head;
		Node* previousNode = new Node;
		while (currentNode != nullptr)
		{
			if (currentNode->info.first == elem)
			{
				int nrOcc = this->head->info.second; // how many elements I deleted
				previousNode->next = currentNode->next;
				delete currentNode;
				this->nrElements -= nrOcc;
				return nrOcc;
			}
			previousNode = currentNode;
			currentNode = currentNode->next;
		}
	}
}


// complexity
// Best Case = Average Case = Worst Case = theta(1) 
int Bag::size() const {
	return this->nrElements;
}

// complexity
// Best Case = Average Case = Worst Case = theta(1) 
bool Bag::isEmpty() const {
	if (this->nrElements == 0)
		return true;
	return false;
}

// complexity
// Best Case = Average Case = Worst Case = theta(1) 
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

// destructor: we go through the list and delete each note
// complexity
// Best Case: theta(1) - bag is empty
// Average Case: theta(nrElements)
// Worst Case: theta(nrElements)
// Overall Complexity: O(nrElements)
Bag::~Bag() {
	Node* currentNode;
	while (this->head != nullptr)           // while list is not empty
	{
		currentNode = this->head;
		this->head = this->head->next;  // go to next node
		delete currentNode;             // delete current head
	}
}

