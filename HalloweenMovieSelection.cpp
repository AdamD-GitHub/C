//************************************************************************************
// Author:  Adam Diel (S0854801)
// Date:    10/23/2018
// 
// Class Name: Halloween Movie Selection
// Class Purpose:
//          This class inputs a media file consisting of hooror movies and prompts the 
//          user to choose three movies they prefer to watch on Halloween.  The selected
//          movies are written to an output file.  
//************************************************************************************
//************************************ CHANGE LOG ************************************
//* Date: 01/01/2000 | Name:                        | ID:
//*-----------------------------------------------------------------------------------
//* Change Description:
//*
//************************************************************************************


#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const string DISP_MOVIE_INIT_01 = "Please review the following list of movies, "
                                  "and choose three for the party.";
const string DISP_MOVIE_INIT_02 = "When you are ready to vote on your movies, "
                                  "press enter:";
const string DISP_MOVIE_SUM_01 = "You have voted for the following horror films:";
const string DISP_MOVIE_SUM_02 = "Poll Selections:";
const string DISP_MOVIE_SUM_NA = "No movies were selected.";
const string DISP_MOVIE_EMPTY = "There are no movies to choose from.";
const string DISP_SELECTION_PROMPT_01 = "Press y to select ";
const string DISP_SELECTION_PROMPT_02 = " or n to reject: ";
const string INVALID_ENTRY = "INVALID ENTRY- Valid entry y or n.";
const string FORMAT_TAB_01 = "\t";
const string FORMAT_TAB_02 = "\t\t";
const string FORMAT_NEW_LINE_01 = "\n";
const string FORMAT_NEW_LINE_02 = "\n\n";

void displayInitPrompt();
void displayMovieRec(string mv);
void displayChoicePrompt(string mv);
void displayMovieSummary(int ms);
void displayInvalidPrompt();
void continueClrScreen();
bool isMovieSelected(int ct, string mv);
bool isInvalidEntry(char ch);
bool isOldCtAndNewCtDiff(int oc, int nc);

int main()
{
	ifstream fin;
	ifstream finmovies;
	ofstream foutmovies;

	string media_title = "";
	int movies_selected = 0;
	int total_record_count = 0;

	fin.open("horror_movies.txt");
	
	displayInitPrompt();

	fin >> media_title;

	if (!fin.eof() || media_title != "")
	{//Checks end of file or empty file
		do 
		{//Read movie records and displays to user 
			displayMovieRec(media_title);
			total_record_count++;
			fin >> media_title;
			if (fin.eof() && media_title != "")
			{//Displays the last read input record
				displayMovieRec(media_title);
				total_record_count++;
			}
		} while (!fin.eof());

		continueClrScreen();

		fin.close();
		fin.open("horror_movies.txt");
		foutmovies.open("party_selections.txt");
		fin >> media_title;

		for (int i = 1 ; i <= total_record_count && movies_selected < 3; i++)
		{//Display movies to user and prompts for up to three selections
			if (isMovieSelected(movies_selected, media_title))
			{//Writes selected record to selection file
				movies_selected++;
				foutmovies << FORMAT_NEW_LINE_01 << media_title;
			}

			fin >> media_title;
		}		

		continueClrScreen();

		fin.close();
		foutmovies.close();
		finmovies.open("party_selections.txt");
		finmovies >> media_title;

		displayMovieSummary(movies_selected);
		for (int i = 1; i <= movies_selected && movies_selected > 0; i++)
		{//Display movie selections
			displayMovieRec(media_title);
			finmovies >> media_title;
		}
				
		finmovies.close();
		continueClrScreen();
	}
	else
	{
		cout << DISP_MOVIE_EMPTY << endl;
		continueClrScreen();

		fin.close();
		foutmovies.close();
	}
	
	return 0;
}

bool isMovieSelected(int ct, string mv)
{//Determine if the user selected the movie and returns status.   
	char choice;
	char choice_peek;
	int new_ct = 0;

	new_ct = ct;

	do 
	{//Prompt user choice question and valid response
		displayChoicePrompt(mv);
		cin >> choice;
		
		choice_peek = cin.peek();
		if (choice_peek != '\n')
		{//Verify only one letter entered. If not, force invalid choice (0)
			choice = 0;
		}
		cin.ignore(100, '\n');

		if (isInvalidEntry(choice))
		{//Display to user choice was invalid
			displayInvalidPrompt();
		}
	} while (isInvalidEntry(choice));

	if (tolower(choice) == 'y') 
		new_ct ++;
	
	return (isOldCtAndNewCtDiff(ct, new_ct));
}

bool isInvalidEntry(char ch)
{//Verify if entry is valid or not	
	if (tolower(ch) == 'y' || tolower(ch) == 'n')
		return false;
	else
		return true;
}

bool isOldCtAndNewCtDiff(int oc, int nc)
{//Compares Old Count to New Count to determine if user selected movie.
	if (oc != nc)
		return true;
	else
		return false;
}

void displayInitPrompt()
{//Display the initial prompt screen to user
	cout << FORMAT_TAB_02 << DISP_MOVIE_INIT_01 << endl;
	cout << FORMAT_TAB_02 << DISP_MOVIE_INIT_02 << endl;
	cout << FORMAT_NEW_LINE_01;
}

void displayMovieRec(string mv)
{//Display movie record to output
	cout << FORMAT_TAB_02 << mv << endl;
}

void displayMovieSummary(int ms)
{//Display movie selection header to user
	cout << FORMAT_TAB_02 << DISP_MOVIE_SUM_01 << endl;
	cout << FORMAT_NEW_LINE_01;
	cout << FORMAT_TAB_02 << DISP_MOVIE_SUM_02 << endl;
	cout << FORMAT_NEW_LINE_01;
	
	if (ms == 0)
	{
		cout << FORMAT_TAB_02 << DISP_MOVIE_SUM_NA << endl;
		cout << FORMAT_NEW_LINE_01;
	}
}

void displayChoicePrompt(string mv)
{//Display choice prompt to user
	cout << FORMAT_TAB_02 << DISP_SELECTION_PROMPT_01 << mv 
		 <<	DISP_SELECTION_PROMPT_02;
}

void displayInvalidPrompt()
{//Display invalid prompt message and user's choice
	cout << FORMAT_NEW_LINE_01;
	cout << FORMAT_TAB_02 << INVALID_ENTRY << endl;
}

void continueClrScreen()
{//Pause and clear screen
	cout << FORMAT_NEW_LINE_02;
	cout << system("pause");
	system("cls");
}