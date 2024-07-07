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

// Function to display admin menu
void displayAdminMenu() {
    cout << "\n--- Welcome to the Student Activity Allocation System (SAAS) ---" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. View Students (ALL and per group)" << endl;
    cout << "3. View Clubs/ Societies" << endl;
    cout << "4. View Sports" << endl;
    cout << "5. Choose Activities for Student" << endl;
    cout << "6. Save all Files" << endl;
    cout << "7. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to read credentials from a file
bool readCredentials(const string& filename, unordered_map<string, string>& credentials) {
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open file " << filename << endl;
        return false;
    }

    string username, password;
    while (file >> username >> password) {
        credentials[username] = password;
    }
    file.close();
    return true;
}

// Function to verify login
bool login(const unordered_map<string, string>& credentials, string& loggedInUser) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    auto it = credentials.find(username);
    if (it != credentials.end() && it->second == password) {
        loggedInUser = username;
        return true;
    } else {
        cout << "Invalid username or password. Please try again." << endl;
        return false;
    }
}

// Function to load activities from a file
vector<Activity> loadActivities(const string& filename) {
    vector<Activity> activities;
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open file " << filename << endl;
        return activities;
    }

    Activity activity;
    while (file >> activity.name >> activity.capacity >> activity.maleCount >> activity.femaleCount) {
        activities.push_back(activity);
    }
    file.close();
    return activities;
}

// Function to load students from a CSV file
vector<Student> loadStudents(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    if (!file) {
        cerr << "Unable to open file " << filename << endl;
        return students;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        Student student;
        string activities;

        getline(iss, student.admissionNumber, ',');
        getline(iss, student.firstName, ',');
        getline(iss, student.surname, ',');
        iss >> student.gender;
        iss.ignore();
        iss >> student.age;
        iss.ignore();
        iss >> student.group;
        iss.ignore();
        getline(iss, activities);

        istringstream activityStream(activities);
        string activity;
        while (getline(activityStream, activity, ',')) {
            student.activities.push_back(activity);
        }

        students.push_back(student);
    }
    file.close();
    return students;
}

// Function to save students to a CSV file
void saveStudents(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Unable to open file " << filename << endl;
        return;
    }

    file << "Admission Number,First Name,Surname,Gender,Age,BBIT Group,Activities" << endl;
    for (const auto& student : students) {
        file << student.admissionNumber << "," << student.firstName << "," << student.surname << ","
             << student.gender << "," << student.age << "," << student.group << ",";
        for (size_t i = 0; i < student.activities.size(); ++i) {
            file << student.activities[i];
            if (i < student.activities.size() - 1) {
                file << ",";
            }
        }
        file << endl;
    }
    file.close();
}

// Function to save activities to a file
void saveActivities(const vector<Activity>& activities, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Unable to open file " << filename << endl;
        return;
    }

    for (const auto& activity : activities) {
        file << activity.name << " " << activity.capacity << " "
             << activity.maleCount << " " << activity.femaleCount << endl;
    }
    file.close();
}

// Function to add a student
void addStudent(vector<Student>& students, unordered_map<string, string>& studentCredentials) {
    Student student;
    cout << "Enter admission number: ";
    cin >> student.admissionNumber;
    for (const auto& existingStudent : students) {
        if (existingStudent.admissionNumber == student.admissionNumber) {
            cout << "Student with the same admission number already exists." << endl;
            return;
        }
    }
    cout << "Enter first name: ";
    cin >> student.firstName;
    cout << "Enter surname: ";
    cin >> student.surname;
    cout << "Enter gender (M/F): ";
    cin >> student.gender;
    cout << "Enter age: ";
    cin >> student.age;
    cout << "Enter BBIT group (A/B/C): ";
    cin >> student.group;

    string password;
    cout << "Set a password for the student: ";
    cin >> password;
    studentCredentials[student.admissionNumber] = password;

    students.push_back(student);
    cout << "Student added successfully." << endl;
}

// Function to view all students
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

// Function to view students by group
void viewStudentsByGroup(const vector<Student>& students) {
    char group;
    cout << "Enter group (A/B/C): ";
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

// Function to display all clubs/societies
void viewClubs(const vector<Activity>& clubs) {
    if (clubs.empty()) {
        cout << "No clubs/societies to display." << endl;
        return;
    }

    for (const auto& club : clubs) {
        cout << "Club/Society: " << club.name << endl;
        cout << "Capacity: " << club.capacity << endl;
        cout << "Male Count: " << club.maleCount << endl;
        cout << "Female Count: " << club.femaleCount << endl;
        cout << "-----------------------------" << endl;
    }
}

// Function to display all sports
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

// Function to display student records
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

// Function to choose activities for a student
void chooseActivities(Student& student, vector<Activity>& clubs, vector<Activity>& sports) {
    cout << "Choose activities for " << student.firstName << " " << student.surname << " (" << student.admissionNumber << "):" << endl;
    cout << "1. Clubs/Societies" << endl;
    cout << "2. Sports" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        int clubCount = 0;
        for (auto& club : clubs) {
            if (clubCount >= 2) {
                break;
            }
            char response;
            cout << "Do you want to join " << club.name << "? (Y/N): ";
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
            cout << "Do you want to join " << sport.name << "? (Y/N): ";
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
            cout << "Do you want to join " << club.name << "? (Y/N): ";
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

// Function to view students with activities chosen by group
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

int main() {
    unordered_map<string, string> adminCredentials;
    unordered_map<string, string> studentCredentials;

    if (!readCredentials("adminlogininfo.txt", adminCredentials)) {
        return 1;
    }

    string loggedInUser;
    while (!login(adminCredentials, loggedInUser)) {}

    vector<Student> students = loadStudents("listofstudents.csv");
    vector<Activity> clubs = loadActivities("clubs.txt");
    vector<Activity> sports = loadActivities("sports.txt");

    while (true) {
        displayAdminMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students, studentCredentials);
                break;
            case 2:
                viewAllStudents(students);
                break;
            case 3:
                viewClubs(clubs);
                break;
            case 4:
                viewSports(sports);
                break;
            case 5:
                if (!students.empty()) {
                    string admissionNumber;
                    cout << "Enter admission number of the student: ";
                    cin >> admissionNumber;

                    auto it = find_if(students.begin(), students.end(), [&admissionNumber](const Student& student) {
                        return student.admissionNumber == admissionNumber;
                    });

                    if (it != students.end()) {
                        chooseActivities(*it, clubs, sports);
                    } else {
                        cout << "Student not found." << endl;
                    }
                } else {
                    cout << "No students available." << endl;
                }
                break;
            case 6:
                saveStudents(students, "listofstudents.csv");
                saveActivities(clubs, "clubs.txt");
                saveActivities(sports, "sports.txt");
                cout << "All data saved successfully." << endl;
                break;
            case 7:
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
