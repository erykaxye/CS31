#include <iostream>
#include <string>
#include <cassert>
using namespace std; 

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);


int main()
{
	
	string people[5] = { "clark", "peter", "diana", "tony", "selina" };
	assert(appendToAll(people, 3, "!!!") == 3);
	cerr << people[0] << people[1] << people[2] << endl;

	assert(lookup(people, 5, "tony") == 3);

	assert(positionOfMax(people, 5) == 3);
	
	assert(rotateLeft(people, 5, 2) == 2);
	for (int o = 0;  o < 5; o++)
		cerr << people[o];
	cerr << endl;
	string super[5] = { "logan", "clark", "peter", "sue", "reed" };
	assert(rotateLeft(super, 5, 5) == -1);
	for (int i = 0; i < 5; i++)
		cerr << super[i];
	cerr << endl; 
	
	string d[9] = {"tony", "bruce", "steve", "steve", "diana", "diana", "diana", "steve", "brian"};
	assert(countRuns(d, 9) == 6);

	string folks[6] = { "bruce", "steve", "", "tony", "sue", "clark" };
	assert(flip(folks, 4) == 4);
	for (int j = 0; j < 6; j++)
		cerr << folks[j];
	cerr << endl; 

	string hey[6] = { "bruce", "steve", "", "tony", "sue", "clark" };
	string group[5] = { "bruce", "steve", "clark", "", "tony" };
	assert(differ(hey, 6, group, 5) == 2);  //  returns 2
	assert(differ(hey, 2, group, 1) == 1);  //  returns 1

	string names[10] = { "logan", "reed", "sue", "selina", "bruce", "peter" };
	string names1[10] = { "reed", "sue", "selina" };
	assert(subsequence(names, 6, names1, 3) == 1);  // returns 1
	string names2[10] = { "logan", "selina" }; // returns -1
	assert(subsequence(names, 5, names2, 2) == -1);
	assert(subsequence(names, 5, names2, 1) == 0);

	string hero[6] = { "clark", "peter", "reed", "tony", "diana", "bruce" };
	assert(split(hero, 6, "logan") == 3);  //  returns 3
									  // hero must now be
									  //      "clark"  "diana"  "bruce"  "peter"  "tony"  "reed"
									  // or   "diana"  "bruce"  "clark"  "reed"  "peter"  "tony"
									  // or one of several other orderings.
									  // All elements < "logan" (i.e., "diana", "bruce", and "clark")
									  //   come before all others
									  // All elements > "logan" (i.e., "tony", "peter", and "reed")
									  //   come after all others
	for (int k = 0; k < 6; k++)
		cerr << hero[k];
	cerr << endl; 

	string hero2[4] = { "reed", "sue", "peter", "steve" };
	assert(split(hero2, 4, "steve") == 2);  //  returns 2
									   // hero2 must now be either
									   //      "reed"  "peter"  "steve"  "sue"
									   // or   "peter"  "reed"  "steve"  "sue"
									   // All elements < "steve" (i.e., "peter" and "reed") come
									   // before all others.
									   // All elements > "steve" (i.e., "sue") come after all others
	for (int l = 0; l < 4; l++)
		cerr << hero2[l];
	cerr << endl;

}

int appendToAll(string a[], int n, string value) 
{
	if (n < 0)
		return -1;
	else 
		for (int i = 0; i < n; i++)
			a[i] += value;
	return n;
}

int lookup(const string a[], int n, string target)
{
	if (n < 0)
		return -1;
	else
		for (int i = 0; i < n; i++)
			if (a[i] == target)
				return i;
	return -1;
}

int positionOfMax(const string a[], int n)  
{
	if (n <= 0)
		return -1;
	else if (n == 1)
		return 0;
	else
	{
		int max = 0; 
		for (int i = n - 1; i >= 0; i--) //i is the last string
		{
			string s = a[i];
			string r = a[max];
			if (s >= r) //compare last string to first string 
				max = i;
		}
		return max; 
	}
}

int rotateLeft(string a[], int n, int pos)
{
	if (n < 0 || pos < 0 || pos > n - 1) 
		return -1;
	else
	{
		string s = a[pos];
		for (int i = pos; i < n - 1; i++)
			a[i] = a[i + 1];
		a[n - 1] = s; //replace the last element with first string 
		return pos;
	}
}

int countRuns(const string a[], int n)
{
	int counter = 1; 
	if (n < 0)
		return -1;
	else if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else 
		for (int i = 0; i < n - 2; i++)
		{
			if (a[i] != a[i + 1])
				counter++;
		}
	if (a[n - 1] != a[n - 2])
		counter++;
	return counter; 
}

int flip(string a[], int n)
{
	if (n < 0)
		return -1;
	else 
		for (int i = 0; i < n / 2; i++) //compare first and last until the middle 
		{
			int j = (n - 1) - i;
			string s = a[i];
			a[i] = a[j];
			a[j] = s;
		}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) 
{
	if (n1 < 0 || n2 < 0)
		return -1;
	else 
	{
		int n = n1;
		if (n1 > n2) //returns smaller value
			n = n2;

		for (int i = 0; i < n; i++)
			if (a1[i] != a2[i])
				return i;
		return n;
	}
}

int subsequence(const string a1[], int n1, const string a2[], int n2) 
{
	if (n1 < 0 || n2 < 0 || n2 > n1)
		return -1;
	else if (n2 == 0)
		return 0; 
	else if (n2 == 1)
	{
		for (int i = 0; i < n1; i++)
				if (a1[i] == a2[0])
					return i; 
		return -1;
	}
	else
	{
		for (int i = 0; i < n2; i++)
			for (int j = 0; j < n1; j++)
				if (a1[j] == a2[i])
					if(a1[j + 1] == a2[i + 1])
						return j; 
		return -1;
	}
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
		return -1;
	else
	{
		for (int j = 0; j < n1; j++)
			for (int i = 0; i < n2; i++)
				if (a1[j] == a2[i])
					return j;  
		return -1;
	}
}

int split(string a[], int n, string splitter) 
{
	if (n < 0)
		return -1;
	else if (n == 0)
		return 0;
	else
	{
		string s;
		int j = n - 1;
		for (int i = 0; i < j;) //compares last and first value 
		{
			if (a[i] < splitter)
				i++;
			if (a[j] >= splitter)
				j--;
			if (i < j) //switches them if they should be on opposite sides 
			{
				s = a[i];
				a[i] = a[j];
				a[j] = s;
			}
		}
	}
	for (int k = 0; k < n; k++) //returns first place of value greater than splitter 
	{
		string l = a[k];
		if (l >= splitter)
			return k;
	}
	return n;
}

								   