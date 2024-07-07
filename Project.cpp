#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

using namespace std;

struct Student {
    string admissionNumber;
    string firstName;
    string surname;
    char gender;
    int age;
    char group;
    vector<string> activities;
};

struct Activity {
    string name;
    int capacity;
    int maleCount;
    int femaleCount;
};

// View all students
void viewAllStudents(const vector<Student>& students) {
    for (const auto& student : students) {
        cout << "Admission Number: " << student.admissionNumber << endl;
        cout << "First Name: " << student.firstName << endl;
        cout << "Surname: " << student.surname << endl;
        cout << "Gender: " << student.gender << endl;
        cout << "Age: " << student.age << endl;
        cout << "BBIT Group: " << student.group << endl;
        cout << "Activities: ";
        for (const auto& activity : student.activities) {
            cout << activity << " ";
        }
        cout << endl;
        cout << "-----------------------------" << endl;
    }
}

// View students by group
void viewStudentsByGroup(const vector<Student>& students) {
    char group;
    cout << "Group (A/B/C): ";
    cin >> group;

    bool found = false;
    for (const auto& student : students) {
        if (student.group == group) {
            cout << "Admission Number: " << student.admissionNumber << endl;
            cout << "First Name: " << student.firstName << endl;
            cout << "Surname: " << student.surname << endl;
            cout << "Gender: " << student.gender << endl;
            cout << "Age: " << student.age << endl;
            cout << "BBIT Group: " << student.group << endl;
            cout << "Activities: ";
            for (const auto& activity : student.activities) {
                cout << activity << " ";
            }
            cout << endl;
            cout << "-----------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No students found in group " << group << "." << endl;
    }
}

// Display all clubs
void viewClubs(const vector<Activity>& clubs) {
    if (clubs.empty()) {
        cout << "No clubs to display." << endl;
        return;
    }

    for (const auto& club : clubs) {
        cout << "Club: " << club.name << endl;
        cout << "Capacity: " << club.capacity << endl;
        cout << "Male Count: " << club.maleCount << endl;
        cout << "Female Count: " << club.femaleCount << endl;
        cout << "-----------------------------" << endl;
    }
}

// Display all sports
void viewSports(const vector<Activity>& sports) {
    if (sports.empty()) {
        cout << "No sports to display." << endl;
        return;
    }

    for (const auto& sport : sports) {
        cout << "Sport: " << sport.name << endl;
        cout << "Capacity: " << sport.capacity << endl;
        cout << "Male Count: " << sport.maleCount << endl;
        cout << "Female Count: " << sport.femaleCount << endl;
        cout << "-----------------------------" << endl;
    }
}
// Display student records
void viewStudentRecord(const Student& student) {
    cout << "Admission Number: " << student.admissionNumber << endl;
    cout << "First Name: " << student.firstName << endl;
    cout << "Surname: " << student.surname << endl;
    cout << "Gender: " << student.gender << endl;
    cout << "Age: " << student.age << endl;
    cout << "BBIT Group: " << student.group << endl;
    cout << "Activities: ";
    for (const auto& activity : student.activities) {
        cout << activity << " ";
    }
    cout << endl;
    cout << "-----------------------------" << endl;
}