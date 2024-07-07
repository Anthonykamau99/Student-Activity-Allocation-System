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

// Choose activities for a student
void chooseActivities(Student& student, vector<Activity>& clubs, vector<Activity>& sports) {
    cout << "Choose activities for " << student.firstName << " " << student.surname << " (" << student.admissionNumber << "):" << endl;
    cout << "1. Clubs" << endl;
    cout << "2. Sports" << endl;
    cout << "Your choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        int clubCount = 0;
        for (auto& club : clubs) {
            if (clubCount >= 2) {
                break;
            }
            char response;
            cout << "Join " << club.name << "? (Y/N): ";
            cin >> response;
            if (toupper(response) == 'Y' && club.capacity > 0) {
                student.activities.push_back(club.name);
                club.capacity--;
                if (student.gender == 'M') {
                    club.maleCount++;
                } else {
                    club.femaleCount++;
                }
                clubCount++;
            }
        }
    } else if (choice == 2) {
        for (auto& sport : sports) {
            char response;
            cout << "Join " << sport.name << "? (Y/N): ";
            cin >> response;
            if (toupper(response) == 'Y' && sport.capacity > 0) {
                student.activities.push_back(sport.name);
                sport.capacity--;
                if (student.gender == 'M') {
                    sport.maleCount++;
                } else {
                    sport.femaleCount++;
                }
                break;
            }
        }

        int clubCount = 0;
        for (auto& club : clubs) {
            if (clubCount >= 2) {
                break;
            }
            char response;
            cout << "Join " << club.name << "? (Y/N): ";
            cin >> response;
        
            if (toupper(response) == 'Y' && club.capacity > 0) {
                student.activities.push_back(club.name);
                club.capacity--;
                if (student.gender == 'M') {
                    club.maleCount++;
                } else {
                    club.femaleCount++;
                }
                clubCount++;
            }
        }
    } else {
        cout << "Invalid choice. No activities chosen." << endl;
    }
}

// View students with activities chosen by group
void viewGroupedStudents(const vector<Student>& students) {
    for (char group = 'A'; group <= 'C'; group++) {
        cout << "Group " << group << ":" << endl;
        for (const auto& student : students) {
            if (student.group == group) {
                viewStudentRecord(student);
            }
        }
    }
}

