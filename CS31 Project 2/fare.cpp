#include <iostream>
#include <string> 
using namespace std; 

int main()
{
	cout << "Age of rider: ";
	int age; 
	cin >> age;
	cin.ignore(10000, '\n');

	cout << "Student? (y/n): ";
	string student;
	getline(cin, student);

	cout << "Destination: ";
	string des; 
	getline(cin, des);

	cout << "Number of zone boundaries crossed: ";
	int zone; 
	cin >> zone; 
	
	double fare = 1.35;
	double zoneFare = 0.55; 
	int zonec = zone;

	if (zone <= 1)
	{
		if (age <= 18)
		{
			fare = 0.65;
			zoneFare = 0;
		}

		if (student == "y")
		{
			fare = 0.65;
			zoneFare = 0;
		}	
	}

	if (age >= 65)
	{
		if (student == "y")
		{
			if (zone > 1)
			{
				fare = 0.55;
				zoneFare = 0.25;
			}
			else
			{
				fare = 0.65;
				zoneFare = 0;
			}
		}
		else
		{
			if (zone < 1)
			{
				fare = 0.45;
				zonec = 0;
			}
			else
			{
				fare = 0.55;
				zoneFare = 0.25;
			}
		}
	}

	double total = fare + zoneFare * zonec;

	cout << "---" << endl;

	if (age <= 0)
		cout << "The age must not be negative" << endl;

	else if (student != "y" && student != "n")
		cout << "You must enter y or n" << endl;

	else if (des == "")
		cout << "You must enter a destination" << endl;

	else if (zone < 0)
		cout << "The number of zone boundaries crossed must not be negative" << endl;

	else
	{
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << "The fare to " << des << " is $" << total << endl;
	}
}