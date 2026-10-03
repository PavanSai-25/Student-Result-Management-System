// Student Result Management System - C++ DSA Mini Project (Group 2)
// Concepts: struct, 1D array (marks), vector (STL), string,
//           linear search, bubble sort, input validation

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

const int NUM_SUBJECTS = 5;   // number of subjects per student
const int PASS_MARK    = 35;  // minimum marks needed in each subject
const int PASS_PERCENT = 40;  // minimum overall percentage

const string SUBJECTS[NUM_SUBJECTS] = {"Maths", "Physics", "Chemistry", "English", "CS"};

// One student = one structure
struct Student {
    int    rollNo;
    string name;
    int    marks[NUM_SUBJECTS];  // 1D array of subject marks
    int    total;
    float  percentage;
    string grade;
    bool   passed;
};

vector<Student> students;  // STL container holding all records

// ---------- Input helpers (validation) ----------

// Read an integer between lo and hi; keeps asking until valid
int readInt(const string &prompt, int lo, int hi) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= lo && value <= hi) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        if (cin.eof()) { cout << "\nInput closed. Exiting.\n"; exit(0); }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid input. Enter a number from " << lo << " to " << hi << ".\n";
    }
}

// Read a non-empty name
string readName(const string &prompt) {
    string s;
    while (true) {
        cout << prompt;
        getline(cin, s);
        if (cin.eof()) { cout << "\nInput closed. Exiting.\n"; exit(0); }
        if (!s.empty()) return s;
        cout << "  Name cannot be empty.\n";
    }
}

// ---------- Core logic ----------

// Linear search: returns index of roll number, or -1 if not found
int findByRoll(int roll) {
    for (size_t i = 0; i < students.size(); i++)
        if (students[i].rollNo == roll) return (int)i;
    return -1;
}

// Calculate total, percentage and pass/fail
void calculateResult(Student &s) {
    s.total = 0;
    s.passed = true;
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        s.total += s.marks[i];
        if (s.marks[i] < PASS_MARK) s.passed = false;  // failed a subject
    }
    s.percentage = (float)s.total / NUM_SUBJECTS;
    if (s.percentage < PASS_PERCENT) s.passed = false;
}

// Assign grade from percentage (F if the student failed)
void assignGrade(Student &s) {
    if (!s.passed)               s.grade = "F";
    else if (s.percentage >= 90) s.grade = "A+";
    else if (s.percentage >= 80) s.grade = "A";
    else if (s.percentage >= 70) s.grade = "B";
    else if (s.percentage >= 60) s.grade = "C";
    else if (s.percentage >= 50) s.grade = "D";
    else                         s.grade = "E";
}

// ---------- Display helpers ----------

void printHeader() {
    cout << left << setw(8) << "Roll" << setw(18) << "Name";
    for (int i = 0; i < NUM_SUBJECTS; i++) cout << setw(11) << SUBJECTS[i];
    cout << setw(7) << "Total" << setw(9) << "Percent" << setw(7) << "Grade" << "Result\n";
    cout << string(100, '-') << "\n";
}

void printStudent(const Student &s) {
    cout << left << setw(8) << s.rollNo << setw(18) << s.name;
    for (int i = 0; i < NUM_SUBJECTS; i++) cout << setw(11) << s.marks[i];
    cout << setw(7) << s.total << setw(9) << fixed << setprecision(2) << s.percentage
         << setw(7) << s.grade << (s.passed ? "PASS" : "FAIL") << "\n";
}

// ---------- Menu operations ----------

void addStudent() {
    Student s;
    s.rollNo = readInt("Enter roll number (1-99999): ", 1, 99999);
    if (findByRoll(s.rollNo) != -1) {
        cout << "  Error: roll number " << s.rollNo << " already exists.\n";
        return;
    }
    s.name = readName("Enter name: ");
    for (int i = 0; i < NUM_SUBJECTS; i++)
        s.marks[i] = readInt("  Marks in " + SUBJECTS[i] + " (0-100): ", 0, 100);

    calculateResult(s);
    assignGrade(s);
    students.push_back(s);
    cout << "  Student added. Percentage: " << fixed << setprecision(2)
         << s.percentage << "%, Grade: " << s.grade << "\n";
}

void displayAll() {
    if (students.empty()) { cout << "  No records to display.\n"; return; }
    printHeader();
    for (const Student &s : students) printStudent(s);
}

void searchByRoll() {
    if (students.empty()) { cout << "  No records to search.\n"; return; }
    int roll = readInt("Enter roll number to search: ", 1, 99999);
    int idx = findByRoll(roll);
    if (idx == -1) { cout << "  No student found with roll number " << roll << ".\n"; return; }
    printHeader();
    printStudent(students[idx]);
}

void displayTopper() {
    if (students.empty()) { cout << "  No records available.\n"; return; }
    float best = students[0].percentage;
    for (const Student &s : students)
        if (s.percentage > best) best = s.percentage;

    cout << "  Topper(s) with " << fixed << setprecision(2) << best << "%:\n";
    printHeader();
    for (const Student &s : students)   // prints all in case of a tie
        if (s.percentage == best) printStudent(s);
}

// Bubble sort, descending by percentage
void sortByPercentage() {
    if (students.empty()) { cout << "  No records to sort.\n"; return; }
    int n = (int)students.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].percentage < students[j + 1].percentage) {
                swap(students[j], students[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;  // already sorted
    }
    cout << "  Sorted by percentage (highest first):\n";
    displayAll();
}

void displayFailed() {
    if (students.empty()) { cout << "  No records available.\n"; return; }
    bool found = false;
    for (const Student &s : students) {
        if (!s.passed) {
            if (!found) { printHeader(); found = true; }
            printStudent(s);
        }
    }
    if (!found) cout << "  No failed students. Everyone passed!\n";
}

void deleteStudent() {
    if (students.empty()) { cout << "  No records to delete.\n"; return; }
    int roll = readInt("Enter roll number to delete: ", 1, 99999);
    int idx = findByRoll(roll);
    if (idx == -1) { cout << "  No student found with roll number " << roll << ".\n"; return; }
    students.erase(students.begin() + idx);
    cout << "  Record deleted.\n";
}

void showMenu() {
    cout << "\n===== STUDENT RESULT MANAGEMENT SYSTEM =====\n"
         << " 1. Add student\n"
         << " 2. Display all students\n"
         << " 3. Search student by roll number\n"
         << " 4. Display topper\n"
         << " 5. Sort students by percentage\n"
         << " 6. Display failed students\n"
         << " 7. Delete student\n"
         << " 8. Exit\n";
}

int main() {
    int choice;
    do {
        showMenu();
        choice = readInt("Enter your choice (1-8): ", 1, 8);
        switch (choice) {
            case 1: addStudent();       break;
            case 2: displayAll();       break;
            case 3: searchByRoll();     break;
            case 4: displayTopper();    break;
            case 5: sortByPercentage(); break;
            case 6: displayFailed();    break;
            case 7: deleteStudent();    break;
            case 8: cout << "Goodbye!\n"; break;
        }
    } while (choice != 8);
    return 0;
}