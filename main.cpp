#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_CAPACITY = 50;

struct Student {
    int id;
    string name;
};

// Function Prototypes
int findStudentById(const Student roster[], int count, int targetId, int &comparisons);
bool addStudent(Student roster[], int &count, int id, const string &name);
bool removeStudentById(Student roster[], int &count, int targetId);
bool safeGetRecord(const Student roster[], int count, int index, Student &outStudent);
void printRoster(const Student roster[], int count);

int main() {
    Student roster[MAX_CAPACITY];
    int currentCount = 0;
    int choice = 0;

    do {
        cout << "\n=========================================\n";
        cout << "     NTC CC105: STUDENT ROSTER MANAGER\n";
        cout << "=========================================\n";
        cout << "1. Add Student Record\n";
        cout << "2. Search Student by ID\n";
        cout << "3. Remove Student by ID\n";
        cout << "4. Safe Inspect Record by Index\n";
        cout << "5. Display Full Roster\n";
        cout << "6. Exit\n";
        cout << "Enter selection [1-6]: ";

        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name;

                cout << "\nEnter Student ID: ";
                cin >> id;

                cout << "Enter Student Name: ";
                cin.ignore();
                getline(cin, name);

                if (addStudent(roster, currentCount, id, name)) {
                    cout << "Student added successfully.\n";
                } else {
                    cout << "Unable to add student.\n";
                }

                break;
            }

            case 2: {
                if (currentCount == 0) {
                    cout << "\nRoster is currently empty.\n";
                    break;
                }

                int targetId;
                int comparisons = 0;

                cout << "\nEnter Student ID to search: ";
                cin >> targetId;

                int index = findStudentById(
                    roster,
                    currentCount,
                    targetId,
                    comparisons
                );

                if (index != -1) {
                    cout << "\nStudent found!\n";
                    cout << "Index: " << index << "\n";
                    cout << "ID: " << roster[index].id << "\n";
                    cout << "Name: " << roster[index].name << "\n";
                } else {
                    cout << "\nStudent not found.\n";
                }

                cout << "Total comparisons: " << comparisons << "\n";

                break;
            }

            case 3: {
                if (currentCount == 0) {
                    cout << "\nRoster is currently empty.\n";
                    break;
                }

                int targetId;

                cout << "\nEnter Student ID to remove: ";
                cin >> targetId;

                if (removeStudentById(roster, currentCount, targetId)) {
                    cout << "Student removed successfully.\n";
                } else {
                    cout << "Student ID not found.\n";
                }

                break;
            }

            case 4: {
                if (currentCount == 0) {
                    cout << "\nRoster is currently empty.\n";
                    break;
                }

                int index;
                Student student;

                cout << "\nEnter index to inspect: ";
                cin >> index;

                if (safeGetRecord(roster, currentCount, index, student)) {
                    cout << "\nRecord found!\n";
                    cout << "Index: " << index << "\n";
                    cout << "ID: " << student.id << "\n";
                    cout << "Name: " << student.name << "\n";
                } else {
                    cout << "\nInvalid index. Out of bounds.\n";
                }

                break;
            }

            case 5:
                printRoster(roster, currentCount);
                break;

            case 6:
                cout << "\nExiting system. Memory cleaned successfully.\n";
                break;

            default:
                cout << "\nInvalid choice. Please enter 1 to 6.\n";
        }

    } while (choice != 6);

    return 0;
}

// Search for a student using Linear Search
int findStudentById(
    const Student roster[],
    int count,
    int targetId,
    int &comparisons
) {
    comparisons = 0;

    for (int i = 0; i < count; i++) {
        comparisons++;

        if (roster[i].id == targetId) {
            return i;
        }
    }

    return -1;
}

// Add a student to the roster
bool addStudent(
    Student roster[],
    int &count,
    int id,
    const string &name
) {
    if (count >= MAX_CAPACITY) {
        cout << "Roster is full. Maximum capacity is "
             << MAX_CAPACITY << ".\n";
        return false;
    }

    int comparisons = 0;

    int existingIndex = findStudentById(
        roster,
        count,
        id,
        comparisons
    );

    if (existingIndex != -1) {
        cout << "Duplicate ID is not allowed.\n";
        return false;
    }

    roster[count].id = id;
    roster[count].name = name;
    count++;

    return true;
}

// Remove a student and shift remaining records to the left
bool removeStudentById(
    Student roster[],
    int &count,
    int targetId
) {
    int comparisons = 0;

    int index = findStudentById(
        roster,
        count,
        targetId,
        comparisons
    );

    if (index == -1) {
        return false;
    }

    for (int i = index; i < count - 1; i++) {
        roster[i] = roster[i + 1];
    }

    count--;

    return true;
}

// Safely retrieve a student record using an index
bool safeGetRecord(
    const Student roster[],
    int count,
    int index,
    Student &outStudent
) {
    if (index < 0 || index >= count) {
        return false;
    }

    outStudent = roster[index];

    return true;
}

// Display all student records
void printRoster(
    const Student roster[],
    int count
) {
    if (count == 0) {
        cout << "\nRoster is currently empty.\n";
        return;
    }

    cout << "\n=========================================\n";
    cout << "             FULL STUDENT ROSTER\n";
    cout << "=========================================\n";

    cout << left
         << setw(10) << "Index"
         << setw(15) << "Student ID"
         << setw(30) << "Name"
         << "\n";

    cout << "-----------------------------------------\n";

    for (int i = 0; i < count; i++) {
        cout << left
             << setw(10) << i
             << setw(15) << roster[i].id
             << setw(30) << roster[i].name
             << "\n";
    }

    cout << "-----------------------------------------\n";
    cout << "Total Active Records: " << count << "\n";
}

/*
==================================================
PERFORMANCE REFLECTION
==================================================

11. Random Access vs. Linear Search

safeGetRecord has O(1) time complexity because an array
element can be accessed directly using its index. After
checking that the index is valid, the program immediately
retrieves the record.

findStudentById has O(n) worst-case time complexity
because Linear Search may need to check every active
student record before finding the target ID or determining
that it does not exist.

12. Deletion Cost

Deleting an element from index 0 is more expensive because
all elements after it must be shifted one position to the
left to maintain contiguous array storage. This requires
O(n) operations in the worst case.

Deleting an element from index currentCount - 1 is faster
because it is the last active element. No shifting is
required, so only the record count is decreased, resulting
in O(1) time complexity.
*/
