#pragma once
#include <utility>
#define NULL_TELEM -111111
#define DELETED_TELEM -222222
typedef int TElem;
class SetIterator;

// Representation: hashtable with open adressing and double hashing
class Set {

    friend class SetIterator;

private:
    TElem* elements;
    int capacity;   // make sure m is a prime number in order to reduce collision
    int length;     
    TElem deleted, empty;

    int hCode(TElem k) const; // hash code
    TElem h1(TElem k) const;  // primary hash function
    TElem h2(TElem k) const;  // secondary hash function
    int h(TElem k, int i) const;  // i = probe number
    void resize();
    bool isPrime(int x);
    int firstPrimeGreaterThan(int x);

public:
    //constructor
    Set();

    //adds an element to the set
    //returns true if the element was added, false otherwise (if the element was already in the set and it was not added)
    bool add(TElem e);

    //removes an element from the set
    //returns true if e was removed, false otherwise
    bool remove(TElem e);

    //checks whether an element belongs to the set or not
    bool search(TElem elem) const;

    //returns the number of elements;
    int size() const;

    //check whether the set is empty or not;
    bool isEmpty() const;

    //return an iterator for the set
    SetIterator iterator() const;

    // destructor
    ~Set();

};
