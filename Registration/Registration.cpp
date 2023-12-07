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


void courseGet(Student stuList[], int numStu);


void saveChanges(Student stuList[], int numStu);


void cleanUp(Student stuList[], int numStu);


void displayEverything(Student stuList[], int numStu);


int main()
{
	int stuNum = 0;

	Student* stuList = studentGet(stuNum);

	printf("There are %d student(s)\n", stuNum);

	studentGet(stuList);

	for (int i = 0; i < stuNum; i++)
	{
		printf("%s\n", stuList[i].id);
	}

	courseGet(stuList, stuNum);

	saveChanges(stuList, stuNum);

	displayEverything(stuList, stuNum);

	cleanUp(stuList, stuNum);

	delete[] stuList;
	exit(1);



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

	return 0;
}


void studentNumGet(int& numStu)
{
	char checker = ' ';

	ifstream inFile(STUFILE);

	if (!inFile.is_open())
	{
		cerr << "\nERROR: Input file cannont be opened\n";
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
	inFile.close();

}


void studentGet(Student stuList[])
{
	char line[STUIDSIZE];
	int row = 0;

	ifstream inFile(STUFILE);

	while (inFile.getline(line, STUIDSIZE))
	{
		snprintf(stuList[row].id, STUIDSIZE, line);
		row++;
	}
	inFile.close();

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


void displayEverything(Student stuList[], int numStu)
{
	Node* head = NULL;
	Node* temp = NULL;

	for (int rows = 0; rows < numStu; rows++)
	{
		head = stuList[rows].courses;
		temp = head;
		printf("%s\n", stuList[rows].id);
		while (temp != NULL)
		{
			printf("%s\n", temp->item.id);
			printf("%d\n", temp->item.section);
			printf("%d\n", temp->item.credit);
			temp = temp->next;
		}
		printf("END\n");
	}
}
