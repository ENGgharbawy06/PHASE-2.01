#ifndef PROBING_H
#define PROBING_H

#include <iostream>

enum EntryType { ACTIVE, EMPTY, DELETED };

struct HashEntry {
    int element;
    EntryType info;

    HashEntry(int e = 0, EntryType i = EMPTY)
        : element(e), info(i) {
    }
};

class Probing {
public:
    // Constructor
    explicit Probing(int size = 101);

    // Destructor (Required since we use raw pointers)
    ~Probing();

    bool contains(int x) const;
    void makeEmpty();
    bool insert(int x);
    bool remove(int x);
    void printTable() const;
    int getSize() const;
    int getCapacity() const;

private:
    HashEntry* table;  // Dynamic array replacing std::vector
    int currentSize;   // Number of active elements
    int tableSize;     // Total capacity of the array

    bool isActive(int currentPos) const;
    int findPos(int x) const;
    void rehash();
    int myHash(int x) const;

    // Math helpers
    int nextPrime(int n);
    bool isPrime(int n);
};

#endif