# Student Result Management System

A menu-driven C++ console application that stores student marks, calculates totals and percentages, assigns grades, and reports results. Built as a Data Structures using C++ (CS207) mini project, Group 2.

## Features

| # | Feature | Description |
|---|---|---|
| 1 | Add student | Roll number, name and marks in 5 subjects, with duplicate roll number check |
| 2 | Display all students | Formatted table of every record |
| 3 | Search by roll number | Linear search, with a "not found" message |
| 4 | Display topper | Highest percentage; prints every student in case of a tie |
| 5 | Sort by percentage | Bubble sort, highest first |
| 6 | Display failed students | Lists failures, or says nobody failed |
| 7 | Delete student | Removes a record by roll number |
| 8 | Exit | Ends the program |

Total, percentage, grade and pass/fail are calculated automatically when a student is added.

## Result Rules

- Marks per subject: 0 to 100
- A student **passes** only if every subject is at least **35** and the percentage is at least **40**
- Failing any one subject fails the student, even with a high average

| Percentage | Grade |
|---|---|
| 90 and above | A+ |
| 80 to 89 | A |
| 70 to 79 | B |
| 60 to 69 | C |
| 50 to 59 | D |
| Below 50 (passed) | E |
| Failed | F |

The subject names, number of subjects and pass criteria are constants at the top of the file and can be changed in one place:

```cpp
const int NUM_SUBJECTS = 5;
const int PASS_MARK    = 35;
const int PASS_PERCENT = 40;
```

## Data Structures and Concepts Used

- **Structure:** `struct Student` groups roll number, name, marks, total, percentage, grade and pass flag
- **1D array:** `int marks[NUM_SUBJECTS]` for subject marks, and a string array for subject names
- **STL vector:** `vector<Student>` stores all records and grows dynamically
- **Strings:** names, grades and subject labels
- **Searching:** linear search by roll number (`findByRoll`)
- **Sorting:** bubble sort by percentage with an early exit
- **Functions:** the program is split into small functions; `main()` only runs the menu loop

## Input Validation and Edge Cases

- Invalid menu choice
- Marks outside 0 to 100, or non-numeric input such as letters
- Empty name
- Duplicate roll number
- Searching, sorting, deleting or reporting with no records
- Roll number that does not exist
- No failed students
- Two students tied for topper

## Project Structure

```
.
├── student_result_system.cpp   # complete source code
└── README.md
```

## Requirements

- A C++ compiler (g++ from GCC/MinGW, version supporting C++11 or later)
- Any terminal (PowerShell, Command Prompt, or Linux/macOS terminal)

## How to Compile and Run

**Windows (PowerShell):**

```
g++ student_result_system.cpp -o student_result_system
.\student_result_system
```

**Linux / macOS:**

```
g++ student_result_system.cpp -o student_result_system
./student_result_system
```

If you edit the code, compile again before running.

## Sample Run

Menu:

```
===== STUDENT RESULT MANAGEMENT SYSTEM =====
 1. Add student
 2. Display all students
 3. Search student by roll number
 4. Display topper
 5. Sort students by percentage
 6. Display failed students
 7. Delete student
 8. Exit
Enter your choice (1-8):
```

Result table after adding a few students and sorting:

```
Roll    Name              Maths      Physics    Chemistry  English    CS         Total  Percent  Grade  Result
----------------------------------------------------------------------------------------------------
101     Asha              90         95         88         92         97         462    92.40    A+     PASS
103     Meena             99         50         60         70         80         359    71.80    B      PASS
102     Ravi              20         80         70         60         50         280    56.00    F      FAIL
```

Ravi fails despite a 56% average because his Maths mark is below 35.

## Demo Input

Use these values to show every feature and the main edge cases. Enter them one per line:

| Step | Input | Shows |
|---|---|---|
| 1 | Menu options 2, 4, 5, 6 on an empty list | Empty-record messages |
| 2 | Add roll `101`, `Asha`, marks `90 95 88 92 97` | Normal student, A+ |
| 3 | Add roll `101` again | Duplicate roll number rejected |
| 4 | Add roll `102`, `Ravi`, marks `20 80 70 60 50` | Fails one subject |
| 5 | Add roll `103`, `Meena`, enter `105` and `abc` as marks | Invalid marks rejected |
| 6 | Add roll `104`, `Divya`, marks `97 92 88 95 90` | Ties with Asha for topper |
| 7 | Search `102`, search `999` | Found and not found |
| 8 | Topper, sort, failed list, delete | Remaining features |

To replay a prepared input file in PowerShell:

```
Get-Content input.txt | .\student_result_system
```

## Complexity

| Operation | Time |
|---|---|
| Search by roll number | O(n) |
| Find topper | O(n) |
| Bubble sort | O(n^2) worst case, O(n) best case |
| Add student | O(n) (duplicate check) |
| Delete student | O(n) |

Space used is O(n) for n students.

## Possible Improvements

- Save and load records from a file
- Update a student's marks
- Search by name
- Replace bubble sort with `std::sort` and a comparator
- Use `map<int, Student>` for faster lookup by roll number

## Team

| Name | Contribution |
|---|---|
| Member 1 | |
| Member 2 | |
| Member 3 | |
| Member 4 | |
| Member 5 | |
| Member 6 | |
