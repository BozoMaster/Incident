#ifndef SET_H
#define SET_H

#include <vector>
#include <string>

class Set {
private:
    std::vector<std::string> elements;

public:
    Set();  // Constructor
    void add(const std::string& element);  // Add element to the set
    std::vector<std::string> getElements() const;  // Get all elements of the set
    Set cartesianProduct(const Set& otherSet) const;  // Cartesian product
    Set intersection(const Set& otherSet) const;  // Intersection of two sets
    std::vector<Set> subsets() const;  // Generate all subsets
    void print() const;  // Print the set elements
};

#endif
