#include "Probing.h"

// Constructor
Probing::Probing(int size) {
    tableSize = nextPrime(size);
    table = new HashEntry[tableSize]; // Allocate memory manually
    currentSize = 0;
    makeEmpty();
}

// Destructor to prevent memory leaks
Probing::~Probing() {
    delete[] table;
}

// Initialize all cells to EMPTY
void Probing::makeEmpty() {
    currentSize = 0;
    for (int i = 0; i < tableSize; i++) {
        table[i].info = EMPTY;
    }
}

// Check if x exists in the table
bool Probing::contains(int x) const {
    return isActive(findPos(x));
}

// Helper to check if a specific slot is active
bool Probing::isActive(int currentPos) const {
    return currentPos > -1 && table[currentPos].info == ACTIVE;
}

// Find position using Linear Probing
int Probing::findPos(int x) const {
    int currentPos = myHash(x);

    // Loop until we find an empty spot or the element itself
    while (table[currentPos].info != EMPTY && table[currentPos].element != x) {
        currentPos++;

        // Wrap around manually
        if (currentPos >= tableSize) {
            currentPos -= tableSize;
        }
    }
    return currentPos;
}

// Insert x into the table
bool Probing::insert(int x) {
    int currentPos = findPos(x);

    if (isActive(currentPos)) {
        return false; // Already exists
    }

    table[currentPos] = HashEntry(x, ACTIVE);

    // Resize if load factor > 0.5
    if (++currentSize > tableSize / 2) {
        rehash();
    }

    return true;
}

// Lazy delete
bool Probing::remove(int x) {
    int currentPos = findPos(x);
    if (!isActive(currentPos)) {
        return false;
    }

    table[currentPos].info = DELETED;
    return true;
}

// Display table
void Probing::printTable() const {
    for (int i = 0; i < tableSize; i++) {
        if (table[i].info == ACTIVE) {
            std::cout << "[" << i << "]: " << table[i].element << std::endl;
        }
        else if (table[i].info == DELETED) {
            std::cout << "[" << i << "]: DELETED" << std::endl;
        }
        else {
            std::cout << "[" << i << "]: EMPTY" << std::endl;
        }
    }
}

// Simple Modulo Hash
int Probing::myHash(int x) const {
    int val = x % tableSize;
    if (val < 0) val += tableSize;
    return val;
}

// Rehash: Create larger array and move active items
void Probing::rehash() {
    int oldSize = tableSize;
    HashEntry* oldTable = table;

    // Create new table approximately double the size
    tableSize = nextPrime(2 * oldSize);
    table = new HashEntry[tableSize];
    currentSize = 0; // Reset count and let insert() increment it back up

    // Initialize new table
    for (int i = 0; i < tableSize; i++) {
        table[i].info = EMPTY;
    }

    // Move active elements from old table to new table
    for (int i = 0; i < oldSize; i++) {
        if (oldTable[i].info == ACTIVE) {
            insert(oldTable[i].element);
        }
    }

    delete[] oldTable; // Free the old memory
}

// Helper: Find next prime (iterative approach)
int Probing::nextPrime(int n) {
    if (n <= 2) return 2;
    if (n % 2 == 0) n++; // Make it odd

    while (!isPrime(n)) {
        n += 2;
    }
    return n;
}

// Helper: Check prime without cmath
bool Probing::isPrime(int n) {
    if (n == 2 || n == 3) return true;
    if (n == 1 || n % 2 == 0) return false;

    // Check up to sqrt(n) by squaring i
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int Probing::getSize() const {
    return currentSize;
}

int Probing::getCapacity() const {
    return tableSize;
}