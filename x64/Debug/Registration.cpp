// Program to implement a class registration system

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int STUIDSIZE = 5;		// Maximum size for a student ID
const int COURSEIDSIZE = 9;		// Maximum size for a course ID

const char STUFILE[] = "students.txt";
const char COURSEFILE[] = "courses.txt";

// Structure used to define a course registration
struct Course
{
	char id[COURSEIDSIZE];
	int section;
	int credit;
};

// Type definition to define the data type for the list data
typedef Course ListItemType;

// Node structure
struct Node
{
	ListItemType item;
	Node* next;
};

// Structure used to associate a student with the classes they are taking
struct Student
{
	char id[STUIDSIZE];
	Node* courses;
};


int main()
{
	int row = 0;
	int lines = 0;

	ifstream inFile("Students.txt");

	while (!inFile.eof())
	{
		lines++;
		if (inFile.eof())
		{
			inFile.clear();
			inFile.seekg(0, ios::beg);
		}
	}

	cout << lines;

	/*
	int* arr = new int(lines);

	for (row = 0; row < lines; row++)
	{
		inFile >> arr[row];
	}

	for (row = 0; row < lines; row++)
	{
		cout << arr[row] << " ";
	}



	/*int choice;

	do
	{
		cout << "1. Select Student by ID\n";
		cout << "2. Display Selected Student's Schedule\n";
		cout << "3. Add a Course to Student's Schedule\n";
		cout << "4. Remove a Course from Student's Schedule\n";
		cout << "5. Exit\n";
		cout << endl;
		cout << "Select: ";

		// Gets the numeric entry from the menu
		cin >> choice;

		// Makes the 'enter' key that was pressed after the numeric entry be ignored
		cin.ignore();

		switch (choice)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		}

	} while (choice != 5);
	*/
	return 0;
}