# Testing

I tested the different functions of the Student Roster Manager.

## Empty Roster

When I tried to search, remove, or inspect a student without adding any records, the program displayed a message saying that the roster is currently empty.

## Adding Students

I added several students and checked if they were saved in the roster correctly.

## Searching

I searched for a student using the student ID. The program was able to find the student and also displayed the number of comparisons.

## Removing a Student

I added students with IDs 101, 102, 103, and 104. After removing student ID 102, the students with IDs 103 and 104 moved to the left.

## Invalid Index

I tested the indices -1 and 50. The program displayed an error message instead of accessing an invalid array location.

## Capacity

The program is designed to stop adding new students once the roster reaches the maximum capacity of 50.
