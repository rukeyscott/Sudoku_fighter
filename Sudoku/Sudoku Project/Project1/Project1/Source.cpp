// File Prologue
// Title: Sudoku Main
// Author: Anthony, Chad, Jason, Michael, Scott
// CS 2320 Final Project
// Last Edited: 06.24.14
// =====================

#include<iostream>
#include<string>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#pragma comment (lib , "winmm.lib")
#include"Sudoku.h"

using namespace std;

int main()
{

	system("color 4B");
	// sound //
	UINT wDeviceID;  //a device ID so we can keep track of it once we open it.
	DWORD dwReturn;	//a return value..
	MCI_OPEN_PARMS mciOpenParms; //Structure for the MCI_OPEN command
	MCI_PLAY_PARMS mciPlayParms; //Structure for the MCI_PLAY command
	mciOpenParms.lpstrDeviceType = TEXT("waveaudio");
	mciOpenParms.lpstrElementName = TEXT("mortal.wav");
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpenParms))
	{

		cout << "sound file unavailable.\n";
	}
	// The device opened successfully; get the device ID.
	wDeviceID = mciOpenParms.wDeviceID;

	if (dwReturn = mciSendCommand(wDeviceID, MCI_PLAY, 0, NULL))
	{
		mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);

		return (dwReturn);
	}
	// Establish Local variables
	string master_loop = "y", inputFile;
	int in_value;

	// Create pointer to Sudoku Class
	Sudoku *solution;
	
	do // Start of master_loop
	{
		cout << "\n*===*===*===*===*===*===*===*===*===*===*===*===*===*===*" << "\n|\t\t\t\t\t\t\t|" << endl;
		cout << "|\t\t\t FIGHTING            \t\t|" << "\n|\t\t\t\t\t\t\t|" << endl;
		cout << "|     /////  //  //  ////   //////  //   //  //  //     |" << endl;
		cout << "|  *  //     //  //  //  /  //  //  // //    //  //  *  |" << endl;
		cout << "| **  /////  //  //  //  /  //  //  ///      //  //  ** |" << endl;
		cout << "|  *     //  //  //  //  /  //  //  // //    //  //  *  |" << endl;
		cout << "|     /////  //////  ////   //////  //  //   //////     |" << endl;
		cout << "|\t\t\t\t\t\t TM  \t|" << "\n|\t\t\t\t\t\t\t\|" << endl;
		cout << "|      * Anthony * Chad * Jason * Michael * Scott *     |" << endl;
		cout << "*===*===*===*===*===*===*===*===*===*===*===*===*===*===*" << endl;

		// Ask the user to input the path to or a file name
		cout << "\n\nYou must input a Sudoku Fighting file name: ";

		// Read in user input assign the variable
		cin >> inputFile;

		// Attempt to open the file
		fstream inFile(inputFile);

		// If file can not open
		if (!inFile)
		{
			cout << "\nHA!!!!, your puny file "<< inputFile << " is not detected. \nYou have to enter it correctly to fight. \nTry again.\n" << endl;
			system("PAUSE");
			system("CLS");
		}

		// If the file is found continue on with program
		else
		{
			// Create new Sudoku Solution
			solution = new Sudoku;

			// Read data into Sudoku
			while (inFile >> in_value)
			{
				solution->fill_board(in_value);
			}

			// Print inputed Sudoku puzzle
			solution->print_Board();

			// Pause to allow user to view inputed Sudoku puzzle
			cout << "\n\nAre you ready to Fight?\n" << endl;
			system("PAUSE");

			// Call Sudoku Solution
			solution->solve(0, 0);

			// Print solved Sudoku puzzle
			solution->print_Board();

			// Conclusion
			mciOpenParms.lpstrElementName = TEXT("flawless.wav");
			cout << "\n\n\Hooozah! That's why they call me the Sudoku Fighter.\n" << endl;

			do
			{
				// Ask user if they would like to try the program again
				cout << "Would you like to fight again? (y) or (n): ";

				// Read input
				cin >> master_loop;

				// If not valid reponse explain, and promt user to try again
				if (master_loop != "y" && master_loop != "n")
				{
					cout << "\nHA!!!, " << master_loop << " Your fighting skills are not up to par. \nTry again if you are brave enough.\n" << endl;
					system("PAUSE");
				}

				// While loop to ensure that only "y" or "n" is inputed.
			} while (master_loop != "y" && master_loop != "n");
		}

		system("CLS");

	// If user inputs "y" master_loop repeats, if user inputs "n" Program ends
	} while (master_loop == "y");
} // End main()


