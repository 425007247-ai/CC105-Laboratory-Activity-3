# NTC CC105 Student Roster Manager

Laboratory Activity 3: Modular Array Operations and Bounds-Checked Roster Management

## Features

1. Add Student Record
2. Search Student by ID using Linear Search
3. Remove Student Record
4. Safe Record Retrieval by Index
5. Display Full Roster

## Data Structure

The program uses a fixed-capacity static array with a maximum capacity of 50 student records.

## Safety Features

- Prevents duplicate student IDs
- Prevents array overflow
- Checks for invalid array indices
- Shifts elements after deleting a student

## Complexity Analysis

- Safe array access: O(1)
- Linear search: O(n)
- Deletion from the beginning: O(n)
- Deletion from the last position: O(1)

## Course

NTC CC105 - Data Structure with Laboratory
