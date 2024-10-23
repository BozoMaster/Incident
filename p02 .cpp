// TODO: add your information for this project
// ----------------------------------------------


#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "Set.h"

#ifndef MAX_FILE_LENGTH
#define MAX_FILE_LENGTH 255
#endif  // MAX_FILE_LENGTH

using namespace std;  // add this only for main

/*
 * Handle command line error
 */
struct CommandLineException {
    CommandLineException(int max, int provided)
    {
        cout << endl;
        cout << "The number of command line arguments doesn't match." << endl;
        cout << provided << " arguments were entered, and " << max << 
                " are required." << endl;
    }  
};

/*
 * Handle exception when openning a file
 */
struct FileException {
  FileException(const string file) {
    cout << endl << "'" << file << "'" << " could not be opened." << endl;
  }
};

/**
 *  Read the input set from the input stream, and output the subsets 
 *  to the output stream.
 */
void get_subsets(Set &s1, ostream& o) {
	s1.print(o, "A=");  // print the set to the output stream

    int count = 0;

    /*     Please put your code here.      */
    // TODO: get all the subsets of the input set and print the result


    if (count < 2)
        o << "There is " << count << " subset of A." << endl;
    else 
        o << "There are " << count << " subsets of A." << endl;
    o << "--------------------------------" << endl;
}

/**
 *  Read the input sets from the input streams, and output the cartesian product
 *  of these two sets to the output stream.
 */
void get_cartesian_product(Set &s1, Set &s2, ostream& o) {
	Set result;
	s1.print(o, "A = ");    // print set 1 to the output stream
    s2.print(o, "B = ");    // print set 2 to the output stream

    int count = 0;

    /*     Please put your code here.      */
    // TODO: perform the Cartesian Product
    


    result.print(o, "A X B = ");    // print the result to the output stream
    if (count < 2) 
        o << "There is " << count << " element in the Cartesian Product." << endl;
    else 
        o << "There are " << count << " elements in the Cartesian Product." << endl;
    o << "--------------------------------" << endl;
}

/**
 *  Read the input sets from the input streams, and output the intersection
 *  of these two sets to the output stream.
 */
void get_intersection(Set &s1, Set &s2, ostream& o) {
    Set result;
	s1.print(o, "A = ");    // print set 1 to the output stream
    s2.print(o, "B = ");    // print set 2 to the output stream

    /*     Please put your code here.      */
    // TODO: get the intersection of these two sets



    result.print(o, "A ∩ B = ");    // print the result to the output stream
    o << "--------------------------------" << endl;
}

/*
 * The input stream i1 is for the set 1
 * The input stream i2 is for the set 2
 * The output stream o is for the results of Cartesian Product, subsets, and intersection
 */
void manage_p02(istream& i1, istream& i2, ostream& o) {
    Set s1, s2;
	s1.scan(i1);            // read set 1 from the first input stream 1
    s2.scan(i2);            // read set 2 from the second input stream 2

    get_cartesian_product(s1, s2, o);
    get_subsets(s1, o);
    get_intersection(s1, s2, o);
}

/*
 * This program accepts three command line arguments:
 * argv[1] is for the path to the input file for set A
 * argv[2] is for the path to the input file for set B
 * argv[3] is for the path to the output file 
 */
int main(int argc, char* argv[]) {
    const int n_paramters = 3;
    try
    {
        char fn[n_paramters][MAX_FILE_LENGTH]; // file names for input and output


        // If there are not proper amount of parameters from command line
        if (argc != n_paramters + 1) {
		    throw CommandLineException(n_paramters, argc - 1);
        }

        // copy necessary command line parameters
        for (int i = 0; i < n_paramters; i++) {
            strcpy(fn[i], argv[i+1]);
        }

        ifstream i1(fn[0]);
        ifstream i2(fn[1]);
        ofstream o(fn[2]);


        if (!i1)
            throw FileException(fn[0]);
        if (!i2)
            throw FileException(fn[1]);
        if (!o)
            throw FileException(fn[2]);

        manage_p02(i1, i2, o);

        i1.close();
        i2.close();
        o.close();
    }
    catch(...)
      {
        cout << "Program ended with exception." << endl;
        exit(EXIT_FAILURE);
      }
    return 0;
}

