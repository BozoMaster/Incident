#include "Set.h"
#include <iostream>
#include <algorithm>

Set::Set() {}

// Add a new element to the set (if it's not already present)
void Set::add(const std::string& element) {
    if (std::find(elements.begin(), elements.end(), element) == elements.end()) {
        elements.push_back(element);
    }
}

// Get all elements in the set
std::vector<std::string> Set::getElements() const {
    return elements;
}

// Cartesian product of two sets
Set Set::cartesianProduct(const Set& otherSet) const {
    Set result;
    for (const auto& e1 : elements) {
        for (const auto& e2 : otherSet.getElements()) {
            result.add("(" + e1 + "," + e2 + ")");
        }
    }
    return result;
}

// Intersection of two sets
Set Set::intersection(const Set& otherSet) const {
    Set result;
    for (const auto& e : elements) {
        if (std::find(otherSet.getElements().begin(), otherSet.getElements().end(), e) != otherSet.getElements().end()) {
            result.add(e);
        }
    }
    return result;
}

// Generate all subsets of the set
std::vector<Set> Set::subsets() const {
    std::vector<Set> result;
    int n = elements.size();
    for (int i = 0; i < (1 << n); ++i) {  // Iterate through all combinations
        Set subset;
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) {
                subset.add(elements[j]);
            }
        }
        result.push_back(subset);
    }
    return result;
}

// Print the set elements
void Set::print() const {
    std::cout << "{";
    for (size_t i = 0; i < elements.size(); ++i) {
        std::cout << elements[i];
        if (i < elements.size() - 1) std::cout << ",";
    }
    std::cout << "}" << std::endl;
}
