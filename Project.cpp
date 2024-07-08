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

// Show the admin menu options
void showMenu() {
    cout << "\n--- Welcome to Student Activity Allocation System (SAAS) ---" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. View Students" << endl;
    cout << "3. View Clubs" << endl;
    cout << "4. View Sports" << endl;
    cout << "5. Choose Activities" << endl;
    cout << "6. Save Data" << endl;
    cout << "7. Exit" << endl;
    cout << "Your choice: ";
}

// Load user credentials from a file
bool loadCreds(const string& file, unordered_map<string, string>& creds) {
    ifstream infile(file);
    if (!infile) {
        cerr << "Can't open " << file << endl;
        return false;
    }
    string user, pass;
    while (infile >> user >> pass) {
        creds[user] = pass;
    }
    infile.close();
    return true;
}
// Verify login credentials
bool login(const unordered_map<string, string>& creds, string& loggedInUser) {
    string user, pass;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    auto it = creds.find(user);
    if (it != creds.end() && it->second == pass) {
        loggedInUser = user;
        return true;
    } else {
        cout << "Invalid login. Try again." << endl;
        return false;
    }
}

// Load activities from a file
vector<Activity> loadActivities(const string& file) {
    vector<Activity> activities;
    ifstream infile(file);
    if (!infile) {
        cerr << "Can't open " << file << endl;
        return activities;
    }

    Activity act;
    while (infile >> act.name >> act.capacity >> act.maleCount >> act.femaleCount) {
        activities.push_back(act);
    }
    infile.close();
    return activities;
}

// Load students from a CSV file
vector<Student> loadStudents(const string& file) {
    vector<Student> students;
    ifstream infile(file);
    if (!infile) {
        cerr << "Can't open " << file << endl;
        return students;
    }

    string line;
    while (getline(infile, line)) {
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
    infile.close();
    return students;
}

// Save students to a CSV file
void saveStudents(const vector<Student>& students, const string& file) {
    ofstream outfile(file);
    if (!outfile) {
        cerr << "Can't open " << file << endl;
        return;
    }

    outfile << "Admission Number,First Name,Surname,Gender,Age,BBIT Group,Activities" << endl;
    for (const auto& student : students) {
        outfile << student.admissionNumber << "," << student.firstName << "," << student.surname << ","
             << student.gender << "," << student.age << "," << student.group << ",";
        for (size_t i = 0; i < student.activities.size(); ++i) {
            outfile << student.activities[i];
            if (i < student.activities.size() - 1) {
                outfile << ",";
            }
        }
        outfile << endl;
    }
    outfile.close();
}

// Save activities to a file
void saveActivities(const vector<Activity>& activities, const string& file) {
    ofstream outfile(file);
    if (!outfile) {
        cerr << "Can't open " << file << endl;
        return;
    }

    for (const auto& act : activities) {
        outfile << act.name << " " << act.capacity << " "
             << act.maleCount << " " << act.femaleCount << endl;
    }
    outfile.close();
}

// Add a student
void addStudent(vector<Student>& students, unordered_map<string, string>& studentCreds) {
    Student student;
    cout << "Admission number: ";
    cin >> student.admissionNumber;
    for (const auto& existingStudent : students) {
        if (existingStudent.admissionNumber == student.admissionNumber) {
            cout << "Student with this admission number already exists." << endl;
            return;
        }
    }
    cout << "First name: ";
    cin >> student.firstName;

    // Validate first name length
    if (student.firstName.length() < 3) {
        cout << "First name must be at least 3 characters long." << endl;
        return;
    }

    cout << "Surname: ";
    cin >> student.surname;
        // Validate surname length
    if (student.surname.length() < 3) {
        cout << "Surname must be at least 3 characters long." << endl;
        return;
    }

    cout << "Gender (M/F): ";
    cin >> student.gender;
    cout << "Age: ";
    cin >> student.age;

    // Validate age
    if (student.age < 17 || student.age > 40) {
        cout << "Age must be between 17 and 40 to be eligible." << endl;
        return;
    }

    // Prompt for BBIT group
    cout << "BBIT group (A/B/C): ";
    cin >> student.group;

    // Validate BBIT group
    if (student.group < 'A' || student.group > 'C') {
        cout << "Invalid group. Choose A, B, or C." << endl;
        return;
    }
        string password;
    cout << "Set a password for the student: ";
    cin >> password;
    studentCreds[student.admissionNumber] = password;

    students.push_back(student);
    cout << "Student added successfully." << endl;
}