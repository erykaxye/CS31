#include <iostream>
#include <string> 
#include <cctype>
#include <cassert>
using namespace std; 

bool hasCorrectSyntax(string song);
int encodeSong(string song, string& instructions, int& badBeat);
bool isBeat(string beat); //checks if its a beat 
char encodeNote(int octave, char noteLetter, char accidentalSign);
bool isChord(string chord);  // checks if a beat is a chord
int splitChord(string chord); //splits chords into notes and sends back the index of the next note
string formatNote(string note); //formats note into the right form for encodeNote and converts it

int main()
{	
	string instrs;
	int badb;
	instrs = "xxx"; badb = -999; // so we can detect whether these get changed
	assert(encodeSong("D5//D/", instrs, badb) == 0 && instrs == "R H"  &&  badb == -999);
	instrs = "xxx"; badb = -999; // so we can detect whether these get changed
	assert(encodeSong("D5//Z/", instrs, badb) == 1 && instrs == "xxx"  &&  badb == -999);
	assert(encodeSong("D5//D8/", instrs, badb) == 2 && instrs == "xxx"  &&  badb == 3); 
	
	instrs = "xxx"; badb = -999;
	assert(encodeSong("5//D/", instrs, badb) == 1 && instrs == "xxx"  &&  badb == -999);
	assert(encodeSong("D9/", instrs, badb) == 2 && instrs == "xxx"  &&  badb == 1);
	instrs = "xxx"; badb = -999;
	assert(encodeSong("A/", instrs, badb) == 0 &&  badb == -999); 
	assert(encodeSong("A#5/", instrs, badb) == 0 && badb == -999);
	assert(encodeSong("A#5A/", instrs, badb) == 0 && badb == -999);
	assert(encodeSong("A#5A//", instrs, badb) == 0 && badb == -999);
	assert(encodeSong("A#5A//D/", instrs, badb) == 0 && badb == -999);
	assert(isBeat("A"));
	assert(isBeat("C#") == true);
	assert(isBeat("C#3") == true);
	assert(isBeat("C3") == true);
	assert(isBeat("C#0C0DC0DD") == true);
	assert(isBeat("C#0C0#DC0DD") == false);
	assert(isBeat("C#0C00DC0DD") == false);
	assert(isBeat("3") == false);
	assert(isBeat("#") == false);
	assert(isBeat("Z") == false);
	assert(isBeat("13") == false);
	assert(isBeat("") == true); 
	assert(hasCorrectSyntax("3B3DD5//") == false); 
	assert(hasCorrectSyntax("3B3DD5/") == false);
	assert(hasCorrectSyntax("A3B3DD3/") == true ); 
	assert(hasCorrectSyntax("3/") == false );
	assert(hasCorrectSyntax("3") == false);
	assert(hasCorrectSyntax("//") == true);
	assert(hasCorrectSyntax("/") == true);
	assert(hasCorrectSyntax("D5//"));
	assert(!hasCorrectSyntax("D5//Z/"));
	assert(!hasCorrectSyntax("5//D/"));
	assert(!hasCorrectSyntax("D5#//D/"));
	assert(hasCorrectSyntax("D#5//D/"));
	assert(!hasCorrectSyntax("Z/"));
	assert(hasCorrectSyntax("D3/F#3/A3/D4//D3F#3A3D4/"));
	assert(!hasCorrectSyntax("D3/F#3/A3/D4//3F#3A3D4/"));
	assert(!isChord("A"));
	assert(isChord("AA"));
	assert(isChord("A#3A"));
	assert(isChord("A3A#A3"));
	assert(!isChord("A#3"));
	assert(splitChord("A#3A") == 3);
	assert(splitChord("AA") == 1);
	assert(splitChord("A3A") == 2);
	
}

int encodeSong(string song, string& instructions, int& badBeat)
{
	if (hasCorrectSyntax(song))
	{
		string instr = instructions; //just incase the song is unplayable i can reset instructions 
		instructions = "";
		int i = 0;
		int j = 0;
		int counter = 0;
		string beat = "";
		string chord = "";
		string note = "";

		for (i; i < song.size(); i++) //whole thing
		{
			if (song[i] == '/') //checks until the next beat 
			{
				counter++;
				if (beat == "")
					instructions += " ";
				else if (isChord(beat))
				{
					while(j < beat.size())//whole chord //until end of the beat
					{
						if (!isChord(beat))
						{
							if (formatNote(beat) == " ") //if the note is unplayable 
							{
								badBeat = counter;
								instructions = instr;
								return 2;
							}
							chord += formatNote(beat);
							j = beat.size(); 
						}
						else
						{
							note = beat.substr(j, splitChord(beat)); 
							beat = beat.substr(splitChord(beat));
							j = 0; 
							if (formatNote(note) == " ")
							{
								badBeat = counter;
								instructions = instr;
								return 2;
							}
							chord += formatNote(note);
						}
					}
					instructions = instructions + '[' + chord + ']'; //when the chord is finished add brackets
					chord = ""; 
				}
				else //instructions for a note (not a chord) 
				{
					note = beat; 
					if (note != "A" && formatNote(note) == " ") //if note is unplayable 
					{
						badBeat = counter;
						instructions = instr;
						return 2;
					}
					else
						instructions += formatNote(note);
				}
				beat = "";
			}
			else
				beat += song[i]; //adds each character into beat until a /
		}

		if (i == song.size()) //if we check the whole song 
		{
			return 0;
		}
		else if (i == song.size() - 1)
			return 0;
		else
		{
			instructions = instr;
			return 2;
		}
	}
	else //if it doesnt have correctsyntax, return 1
		return 1;

}

bool hasCorrectSyntax(string song) //remember to stay hydrated 
{
	int i = 0;
	string beat = "";
	for (i; i < song.size(); i++) 
	{
		if (song[i] == '/') //checks for a beat 
		{
			if (isBeat(beat))
			{
				beat = "";
				continue;
			}
			else
				return false;
		}
		else
			beat += song[i]; //adds values into beat until a /
	}
	int k = song.size() - 1;
	if (song[k] == '/') //the last character has to be a /
		return true;
	else
		return false;
}

bool isBeat(string beat) 
{
	if (beat.size() == 0) //a rest
		return true;
	for (int i = 0; i < beat.size(); i++) //runs through the whole beat
	{
		if (beat[0] < 'A' || beat[0] > 'G') //first value has to be a letter 
			return false;
		else if (beat[i] >= 'A' && beat[i] <= 'G') //first value
		{
			if (i + 1 == beat.size())
				return true;
			else if (beat[i + 1] >= 'A' && beat[i + 1] <= 'G') //next note
				continue;
			else if (beat[i + 1] == '#' || beat[i + 1] == 'b') //second value 
			{
				if (i + 2 == beat.size())
					return true;
				else if (beat[i + 2] >= 'A' && beat[i + 2] <= 'G')
					continue;
				else if (beat[i + 2] >= '0' && beat[i + 2] <= '9')
					continue;
				else
					return false;
			}
			else if (beat[i + 1] >= '0' && beat[i + 1] <= '9')
			{
				if (i + 2 == beat.size())
					return true;
				else if (beat[i + 2] >= 'A' && beat[i + 2] <= 'G')
					continue;
				else
					return false;
			}
			else
				return false;
		}
		else if (beat[i] == '#' || beat[i] == 'b')
		{
			if (i + 1 == beat.size())
				return true;
			else if (beat[i + 1] >= 'A' && beat[i + 1] <= 'G')
				continue;
			else if (beat[i + 1] >= '0' && beat[i + 1] <= '9')
				continue;
			else
				return false;
		}
		else if (beat[i] >= '0' && beat[i] <= '9')
		{
			if (i + 1 == beat.size())
				return true;
			else if (beat[i + 1] >= 'A' && beat[i + 1] <= 'G')
				continue;
			else
				return false;
		}
		else
			return false;
	}

}

bool isChord(string chord)
{
	for (int i = 0; i < chord.size(); i++)//one beat 
	{
		if (chord[i] >= 'A' && chord[i] <= 'G')
		{
			if (i + 1 == chord.size())
				return false; //not a chord, its a note
			else if (chord[i + 1] >= 'A' && chord[i + 1] <= 'G')
				return true; //more than 1 letter means its a chord 
			else if (chord[i + 1] == '#' || chord[i + 1] == 'b')
			{
				if (i + 2 == chord.size())
					return false; //note
				else if (chord[i + 2] >= 'A' && chord[i + 2] <= 'G')
					return true;
				else if (chord[i + 2] >= '0' && chord[i + 2] <= '9')
					continue;
				else
					return false;
			}
			else if (chord[i + 1] >= '0' && chord[i + 1] <= '9')
			{
				if (i + 2 == chord.size())
					return false; //note
				else if (chord[i + 2] >= 'A' && chord[i + 2] <= 'G')
					return true;
				else
					return false;
			}
			else
				return false;
		}
		else if (chord[i] == '#' || chord[i] == 'b')
		{
			if (i + 1 == chord.size())
				return false; //note
			else if (chord[i + 1] >= 'A' && chord[i + 1] <= 'G')
				return true;
			else if (chord[i + 1] >= '0' && chord[i + 1] <= '9')
				continue;
			else
				return false;
		}
		else if (chord[i] >= '0' && chord[i] <= '9')
		{
			if (i + 1 == chord.size())
				return false;
			else if (chord[i + 1] >= 'A' && chord[i + 1] <= 'G')
				return true; 
			else
				return false;
		}
		else
			return false;
	}
}

int splitChord(string chord)
{
	int i = 0;
	if (chord[i] >= 'A' && chord[i] <= 'G')
	{
		if (chord[i + 1] >= 'A' && chord[i + 1] <= 'G')
		{
			i++;
			return i; //the next note starts at index 2
		}
		else if (chord[i + 1] == '#' || chord[i + 1] == 'b')
		{
			if (chord[i + 2] >= 'A' && chord[i + 2] <= 'G')
			{
				i += 2;
				return i;
			}
			else if (chord[i + 2] >= '0' && chord[i + 2] <= '9')
			{
				i += 3;
				return i;
			}
			else
				return i;
		}
		else if (chord[i + 1] >= '0' && chord[i + 1] <= '9')
		{
			if (chord[i + 2] >= 'A' && chord[i + 2] <= 'G')
			{
				i += 2;
				return i;
			}
			else
				return i;
		}
		else
			return 0;
	}
}

string formatNote(string note)
{
	string newNote = ""; 

	for (int i = 0; i < note.size();)
	{
		if (note[i] >= 'A' && note[i] <= 'G')
		{
			if (i + 1 == note.size()) //default octave and no accidental 
			{
				newNote = encodeNote(4, note[i], ' ');
				return newNote;
			}
			else if (note[i + 1] == '#' || note[i + 1] == 'b')
			{
				if (note[i + 2] >= '0' && note[i + 2] <= '9')
				{
					newNote = encodeNote(note[i + 2] - '0', note[i], note[i + 1]);
					return newNote;
				}
				else //default octave
				{
					newNote = encodeNote(4, note[i], note[i + 1]);
					return newNote;
				}
			}
			else if (note[i + 1] >= '0' && note[i + 1] <= '9')
			{
				newNote = encodeNote(note[i + 1] - '0', note[i], ' ');
				return newNote;
			}
			else
				return newNote;
		}
	}
}

char encodeNote(int octave, char noteLetter, char accidentalSign)
{
	// This check is here solely to report a common CS 31 student error.
	if (octave > 9)
	{
		cerr << "********** encodeNote was called with first argument = "
			<< octave << endl;
	}

	// Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
	//      to -1, 0,   1,   2,   3, ...,  11, 12

	int note;
	switch (noteLetter)
	{
	case 'C':  note = 0; break;
	case 'D':  note = 2; break;
	case 'E':  note = 4; break;
	case 'F':  note = 5; break;
	case 'G':  note = 7; break;
	case 'A':  note = 9; break;
	case 'B':  note = 11; break;
	default:   return ' ';
	}
	switch (accidentalSign)
	{
	case '#':  note++; break;
	case 'b':  note--; break;
	case ' ':  break;
	default:   return ' ';
	}

	// Convert ..., A#1, B1, C2, C#2, D2, ... to
	//         ..., -2,  -1, 0,   1,  2, ...

	int sequenceNumber = 12 * (octave - 2) + note;

	string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
	if (sequenceNumber < 0 || sequenceNumber >= keymap.size())
		return ' ';
	return keymap[sequenceNumber];
}
