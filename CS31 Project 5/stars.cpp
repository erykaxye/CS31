#define _CRT_SECURE_NO_DEPRECATE

#include "utilities.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <random>
#include <utility>
using namespace std;

const int MAXSIZE = 6;
const int MINSIZE = 4;	
const int MAXWORD = 10000; //have to be able to hold at least 9000 cstrings 
const char WORDFILENAME[MAXWORD] = "C:/Users/eryka/Documents/school/erica/college/c++/CS31 Project 5/7000 words.txt"; //get the file with the words in it 

int runOneRound(const char words[][MAXSIZE + 1], int nWords, int wordnum);

int main()
{
	char secretWords[MAXWORD][MAXSIZE + 1] = {}; 
	int nWords = getWords(secretWords, MAXWORD, WORDFILENAME); //number of words 
	//cerr << nWords << endl;

	double tot = 0.0;
	int min = 0;
	int max = 0;

	if (nWords < 1)
		cout << "No words were loaded, so I can't play the game." << endl; 
	else //plays game 
	{
		cout << "How many rounds do you want to play? ";
		int n;
		cin >> n;
		cin.ignore(10000, '\n'); //bc next thing ur inputting is a cstring 

		if (n < 1) //not positive 
			cout << "The number of rounds must be positive." << endl;
		else
		{
			for (int i = 1; i <= n; i++)
			{
				cout << endl << "Round " << i << endl;
				int wordnum = randInt(0, nWords - 1); 
				//cerr << wordnum << endl; 
				char word[MAXSIZE + 1] = "";
				strcpy(word, secretWords[wordnum]); //i feel like i only need a 1d array here IDK WHATS GOING ON but it works i think 
				//cerr << word << endl;
				cout << "The secret word is " << strlen(word) << " letters long." << endl;

				int score = runOneRound(secretWords, nWords, wordnum); 
				//cerr << score << endl; 

				if (score == 1)
					cout << "You got it in 1 try." << endl;
				else if (score > 1)
					cout << "You got it in " << score << " tries." << endl;

				tot += score; 

				if (i == 1)
				{
					min = score;
					max = score; 
				}
				else //next rounds 
				{
					if (max < score)
						max = score; //if the previous score is smaller, then replace, if previous is bigger or the same theres no change 					
					if (min > score)
						min = score; //if previous score is larger, then replace, if previous score smaller or the same no change 
				}
				cout.setf(ios::fixed);
				cout.precision(2);
				cout << "Average: " << tot / i << ", minimum: " << min << ", maximum: " << max << endl;

			}
		}
	}
}

int runOneRound(const char words[][MAXSIZE + 1], int nWords, int wordnum)
{
	if (nWords < 1 || wordnum < 0 || wordnum >= nWords) //stay hydrated b****
		return -1;
	
	int score = 0;

	for (;;)//run probe word until u win and return score 
	{ 
		int stars = 0;
		int planets = 0;
		int ok = 0;
		int m = 0;
		char probe[101] = ""; 
		cout << "Probe word: ";
		cin.getline(probe, 101); 

		if (strlen(probe) < 4 || strlen(probe) > 6)
		{
			cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			ok++; 
		}
		else
		{
			for (int l = 0; l < strlen(probe); l++)
				if (!islower(probe[l]))
				{
					cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
					ok++;
					break; 
				}
		}

		if (ok == 0)
		{
			for (int n = 0; n < nWords; n++)
				if (strcmp(probe, words[n]) == 0)
					m++;
			if (m == 0)
				cout << "I don't know that word." << endl; 
		}
		
		if(ok == 0 && m != 0)
		{
			for (int i = 0; i < strlen(words[wordnum]); i++) //test each character for star
				if (words[wordnum][i] == probe[i])
				{
					probe[i] = '*'; //replace with * so it can't be a planet 
					stars++;
				}
			if (stars == strlen(words[wordnum]))
			{
				score++;
				return score;
			}
			//test for planets  
			for (int j = 0; j < strlen(words[wordnum]); j++) //until end of the word
			{
				for (int k = 0; k < strlen(probe); k++)//end of the probe word? does this work?
				{
					if (probe[k] == words[wordnum][j]) //switching doesnt work?  
					{
						if (j != k && probe[j] != '*') //if character is a star and if the postion of probe isnt a star 
						{
							probe[k] = '-'; //and not another previous planet? 
							planets++;
							break; //do i still need this the answer is yes 
						}
					}
				}
			}

			cout << "Stars: " << stars; 
			cout << ", Planets: " << planets << endl; 
			cerr << probe << endl;
			score++;
		}
	}
	return score;
}

