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

Student* studentGet(int& numStu);

int binarySearch(const Student stuList[], int left, int right, const char targetID[]);

void selectID(Student stuList[], int& stuNum, int& selectedStudentIndex);

void courseGet(Student stuList[], int numStu);

void displayCourses(Student stuList[], int indexNum, int& classNum);

void findCourses(Student stuList[], int index);

void addCourse(Node*& courseList, const Course& newCourse);

void removeCourse(Student stuList[], int index);

void saveChanges(Student stuList[], int numStu);

void cleanUp(Student stuList[], int numStu);

int main()
{
	int stuNum = 0;
	int selectedIndex = -1;
	int courseTotal = 0;

	Student* stuList = studentGet(stuNum);

	courseGet(stuList, stuNum);

	int choice;

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

		printf("\n");

		// Makes the 'enter' key that was pressed after the numeric entry be ignored
		cin.ignore();

		switch (choice)
		{
		case 1:
			selectID(stuList, stuNum, selectedIndex);
			break;
		case 2:
			displayCourses(stuList, selectedIndex, courseTotal);
			break;
		case 3:
			findCourses(stuList, selectedIndex);
			break;
		case 4:
			removeCourse(stuList, selectedIndex);
			break;
		}

	} while (choice != 5);

	saveChanges(stuList, stuNum);

	cleanUp(stuList, stuNum);

	delete[] stuList;
	return 0;
}


Student* studentGet(int& numStu)
{
	char checker = ' ';

	ifstream inFile(STUFILE);

	if (!inFile.is_open())
	{
		cerr << "\nERROR Input file cannont be opened\n";
		inFile.close();
		exit(1);
	}

	inFile.seekg(-1, ios::end);
	inFile.get(checker);
	if (checker != '\n')
	{
		numStu++;
	}
	inFile.clear();
	inFile.seekg(0, ios::beg);

	while (inFile.get(checker))
	{
		if (checker == '\n')
		{
			numStu++;

		}
	}
	inFile.clear();
	inFile.seekg(0, ios::beg);

	Student* stuList = new Student[numStu];

	char line[STUIDSIZE];

	for (int i = 0; i < numStu; i++)
	{
		inFile.getline(line, STUIDSIZE);
		snprintf(stuList[i].id, STUIDSIZE, line);
	}

	inFile.close();

	return stuList;
}


int binarySearch(const Student stuList[], int left, int right, const char targetID[])
{	// Continue the search as long as the left index is less than or equal to the right index
	if (left <= right)
	{	// Calculate the middle index of the current search range
		int mid = left + (right - left) / 2;

		if (strcmp(stuList[mid].id, targetID) == 0)
		{
			// Found the target student
			return mid;
		}
		else if (strcmp(stuList[mid].id, targetID) < 0)
		{
			return binarySearch(stuList, mid + 1, right, targetID);
		}
		else
		{
			return binarySearch(stuList, left, mid - 1, targetID);
		}
	}

	// Target student ID not found
	return -1;
}

void selectID(Student stuList[], int& stuNum, int& selectedStudentIndex)
{	// Input variable for the target student ID
	char targetID[STUIDSIZE];

	// Prompt the user to enter a student ID
	printf("Enter student ID: ");
	cin >> targetID;

	// Perform binary search to find the student in the array
	int result = binarySearch(stuList, 0, stuNum - 1, targetID);

	// Check the result of the search
	if (result != -1)
	{
		// Display the student is found
		printf("Student selected.\n");
		// Update selected student index
		selectedStudentIndex = result;
	}
	else
	{
		// Display the student was not found
		printf("Student ID not found.\n");
		// Reset the selected student index
		selectedStudentIndex = -1;
	}
	printf("\n");
}


void courseGet(Student stuList[], int numStu)
{
	char line[COURSEIDSIZE];
	char test = ' ';

	int courseSect = 0;
	int creditHrs = 0;
	int counter = 0;
	ifstream inFile(COURSEFILE);

	if (!inFile.is_open())
	{
		cerr << "\nERROR: Input file cannont be opened\n";
		for (counter; counter < numStu; counter++)
		{
			stuList[counter].courses = NULL;
		}
	}
	else
	{
		Node* temp = NULL;


		for (counter = 0; counter < numStu; counter++)
		{
			stuList[counter].courses = NULL;


			inFile.getline(line, COURSEIDSIZE);

			if (strcmp(line, "END") != 0)
			{
				stuList[counter].courses = new Node;
				snprintf(stuList[counter].courses->item.id, COURSEIDSIZE, line);
				inFile >> courseSect;
				stuList[counter].courses->item.section = courseSect;
				inFile >> creditHrs;
				stuList[counter].courses->item.credit = creditHrs;
				stuList[counter].courses->next = NULL;
				temp = stuList[counter].courses;

				inFile.ignore(numeric_limits<streamsize>::max(), '\n');

				inFile.getline(line, COURSEIDSIZE);

				while (strcmp(line, "END") != 0)
				{
					temp->next = new Node;
					temp = temp->next;
					snprintf(temp->item.id, COURSEIDSIZE, line);
					inFile >> courseSect;
					temp->item.section = courseSect;
					inFile >> creditHrs;
					temp->item.credit = creditHrs;
					temp->next = NULL;
					inFile.ignore(numeric_limits<streamsize>::max(), '\n');
					inFile.getline(line, COURSEIDSIZE);
				}
			}

		}
	}
	inFile.close();
}


void displayCourses(Student stuList[], int indexNum, int& classNum)
{
	if (indexNum == -1)
	{
		printf("No student selected \n\n");
		return;
	}
	if (stuList[indexNum].courses == NULL)
	{
		classNum = 0;
		printf("Student is not registered for any courses \n\n");
	}
	else
	{
		Node* head = NULL;
		Node* temp = NULL;

		classNum = 1;

		head = stuList[indexNum].courses;
		temp = head;

		//printf("\n");
		while (temp != NULL)
		{
			printf("%d. %s  Sect: %d  Credit: %d\n", classNum, temp->item.id, temp->item.section, temp->item.credit);
			temp = temp->next;
			classNum++;
		}
		printf("\n\n");
	}
}


void findCourses(Student stuList[], int index)
{	//see if student was selected
	if (index == -1)
	{
		printf("No student selected\n");
	}
	else
	{
		// Get course information
		Course course{};
		printf("Enter course ID: ");
		cin >> course.id;

		printf("Enter section number: ");
		cin >> course.section;

		printf("Enter credit hours: ");
		cin >> course.credit;

		// function call to add course to schedule
		addCourse(stuList[index].courses, course);
	}
	printf("\n");
}


void addCourse(Node*& courseList, const Course& newCourse)
{
	// Create a new node for the new course
	Node* newNode = new Node;
	// Assign the new course to the item of the new node
	newNode->item = newCourse;
	// Set the next pointer of the new node to the current head of the linked list
	newNode->next = courseList;
	// Update the head of the linked list
	courseList = newNode;
}


void removeCourse(Student stuList[], int index)
{
	int courseNum = 0;
	int numOfCourses = 0;

	if (index == -1)
	{
		printf("\nNo student selected \n\n");
	}
	else
	{
		displayCourses(stuList, index, numOfCourses);

		if (numOfCourses == NULL)
		{
			return;
		}

		printf("Choose course to remove\n");
		cin >> courseNum;

		if (!(courseNum > 0 && courseNum < numOfCourses))
		{
			return;
		}

		Node* temp = stuList[index].courses;

		if (courseNum == 1)
		{
			stuList[index].courses = temp->next;

			delete temp;
			return;
		}

		for (int i = 1; temp != NULL && i < courseNum - 1; i++)
		{
			temp = temp->next;
		}

		if (temp == NULL || temp->next == NULL)
		{
			return;
		}

		Node* next = temp->next->next;

		delete temp->next;

		temp->next = next;
	}
	printf("\n");
}


void saveChanges(Student stuList[], int numStu) //maybe have a const on the array
{
	ofstream outFile(COURSEFILE);

	Node* head = NULL;
	Node* temp = NULL;

	for (int rows = 0; rows < numStu; rows++)
	{
		head = stuList[rows].courses;
		temp = head;
		while (temp != NULL)
		{
			outFile << temp->item.id << "\n";
			outFile << temp->item.section << "\n";
			outFile << temp->item.credit << "\n";
			temp = temp->next;
		}
		outFile << "END\n";
	}
	outFile.close();
}


void cleanUp(Student stuList[], int numStu)
{
	for (int i = 0; i < numStu; i++)
	{
		while (stuList[i].courses != NULL)
		{
			Node* temp = stuList[i].courses->next;
			delete stuList[i].courses;
			stuList[i].courses = temp;
		}
	}
}
