#include "Set.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Function to read a set from a file
Set readSetFromFile(const std::string& filename) {
    Set resultSet;
    std::ifstream file(filename);
    std::string word;
    while (file >> word) {
        resultSet.add(word);
    }
    return resultSet;
}

// Function to write the Cartesian product, subsets, and intersection to the output file
void writeResultsToFile(const std::string& filename, const Set& set1, const Set& set2) {
    std::ofstream outFile(filename);

    // Cartesian product
    Set cartesian = set1.cartesianProduct(set2);
    outFile << "Cartesian Product: ";
    cartesian.print();

    // Subsets of Set 1
    std::vector<Set> subsets = set1.subsets();
    outFile << "Subsets of Set 1:\n";
    for (const auto& subset : subsets) {
        subset.print();
    }

    // Intersection
    Set intersection = set1.intersection(set2);
    outFile << "Intersection: ";
    intersection.print();
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <input1.dat> <input2.dat> <output.dat>\n";
        return 1;
    }

    // Read sets from input files
    Set set1 = readSetFromFile(argv[1]);
    Set set2 = readSetFromFile(argv[2]);

    // Write results to output file
    writeResultsToFile(argv[3], set1, set2);

    return 0;
}
