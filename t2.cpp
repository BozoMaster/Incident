#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

using namespace std;

class Student {
private:
    string name;
    int rollNo;
    vector<int> marks;
    float totalMarks;
    float average;
    char grade;

public:
    // Constructor
    Student(string name = "", int rollNo = 0, vector<int> marks = {})
        : name(name), rollNo(rollNo), marks(marks) {
        calculateResults();
    }

    void calculateResults() {
        totalMarks = 0;
        for (int mark : marks) {
            totalMarks += mark;
        }
        average = marks.empty() ? 0 : totalMarks / marks.size();
        grade = determineGrade(average);
    }

    char determineGrade(float avg) const {
        if (avg >= 90) return 'A';
        else if (avg >= 80) return 'B';
        else if (avg >= 70) return 'C';
        else if (avg >= 60) return 'D';
        else return 'F';
    }

    void display() const {
        cout << "Name: " << name 
             << ", Roll No: " << rollNo 
             << ", Total Marks: " << totalMarks 
             << ", Average: " << fixed << setprecision(2) << average 
             << ", Grade: " << grade << endl;
    }

    // Getters
    string getName() const { return name; }
    int getRollNo() const { return rollNo; }
    
    // Setters
    void setMarks(const vector<int>& newMarks) {
        marks = newMarks;
        calculateResults();
    }

    friend ostream& operator<<(ostream& os, const Student& student);
};

ostream& operator<<(ostream& os, const Student& student) {
    os << student.name << "," << student.rollNo;
    for (int mark : student.marks) {
        os << "," << mark;
    }
    return os;
}

void saveToFile(const vector<Student>& students) {
    ofstream outFile("students.dat");
    
    if (!outFile.is_open()) {
        throw runtime_error("Unable to open file for writing.");
    }

    for (const auto& student : students) {
        outFile << student << endl;
    }
    
    outFile.close();
}

vector<Student> loadFromFile() {
    vector<Student> students;
    ifstream inFile("students.dat");
    
    if (!inFile.is_open()) {
        throw runtime_error("Unable to open file for reading.");
    }
    
    string line;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string name;
        int rollNo;

        getline(ss, name, ',');
        ss >> rollNo;

        vector<int> marks;
        string markStr;

        while (getline(ss, markStr, ',')) {
            marks.push_back(stoi(markStr));
        }

        students.emplace_back(name, rollNo, marks);
    }
    
    inFile.close();
    return students;
}

void addStudent(vector<Student>& students) {
    string name;
    int rollNo;

    cout << "Enter Name: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, name);

    cout << "Enter Roll No: ";
    cin >> rollNo;

    vector<int> marks(5); // Assuming 5 subjects
    cout << "Enter Marks for 5 subjects: ";
    
    for (int i = 0; i < 5; ++i) {
        cin >> marks[i];
    }

    students.emplace_back(name, rollNo, marks);
}

void updateStudent(vector<Student>& students) {
   int rollNo;

   cout << "Enter Roll No of the student to update: ";
   cin >> rollNo;

   for (auto& student : students) {
       if (student.getRollNo() == rollNo) {
           vector<int> newMarks(5);
           cout << "Enter new Marks for 5 subjects: ";
           for (int i = 0; i < 5; ++i) {
               cin >> newMarks[i];
           }
           student.setMarks(newMarks);
           cout << "Student updated successfully!" << endl;
           return;
       }
   }

   cout << "Student not found!" << endl;
}

void deleteStudent(vector<Student>& students) {
   int rollNo;

   cout << "Enter Roll No of the student to delete: ";
   cin >> rollNo;

   auto it = remove_if(students.begin(), students.end(),
                       [rollNo](const Student& s) { return s.getRollNo() == rollNo; });

   if (it != students.end()) {
       students.erase(it, students.end());
       cout << "Student deleted successfully!" << endl;
   } else {
       cout << "Student not found!" << endl;
   }
}

void showResults(const vector<Student>& students) {
   if (students.empty()) {
       cout << "No records available." << endl;
       return;
   }

   for (const auto& student : students) {
       student.display();
   }
}

int main() {
   vector<Student> students;

   try {
       // Load existing data from file
       students = loadFromFile();
   } catch (const runtime_error& e) {
       cerr << e.what() << endl; // Handle file loading error
       return 1; // Exit if unable to load data
   }

   while (true) {
       cout << "\n1. Add Student\n2. Update Student\n3. Delete Student\n4. Show Results\n5. Exit\n";
       int choice;
       cin >> choice;

       switch (choice) {
           case 1:
               addStudent(students);
               break;
           case 2:
               updateStudent(students);
               break;
           case 3:
               deleteStudent(students);
               break;
           case 4:
               showResults(students);
               break;
           case 5:
               try {
                   saveToFile(students); // Save data before exit
               } catch (const runtime_error& e) {
                   cerr << e.what() << endl; // Handle file saving error
                   return 1; // Exit if unable to save data
               }
               return 0;
           default:
               cout << "Invalid choice!" << endl;
       }
   }
}