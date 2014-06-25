// File Prologue
// Title: Sudoku Header
// Author: Anthony, Chad, Jason, Michael, Scott
// CS 2320 Final Project
// Last Edited: 06.24.14
// =====================

using namespace std;

// Establish constants for Board Multi-Demensional Array
const int ROW = 9;
const int MAX = 81;

// Sudoku Class
class Sudoku
{
public:

	// Initialize Sudoku Local Variables
	Sudoku()
	{
		int i, j; // Local variable to help establish board

		// Multi Demensional Array is initialized. 
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < ROW; j++)
				Board[i][j] = 0;
		}
	}

	// fill_board Function
	void fill_board(int data)
	{
		// Assign data to source Array
		source[in_total] = data;
		in_total++;
				
		// Once source Array = 81 (full) fill board
		if (in_total == MAX)
		{
			int row_row = 0; // Local Variable

			for (int i = 0; i < ROW; i++)
			{
				for (int j = 0; j < ROW; j++)
				{
					Board[i][j] = source[row_row];
					row_row++;
				}
			}
		}
	}

	// validate_row Function
	bool validate_Row(int row)
	{
		int i; // Local Variable

		/* Clear the checker array slots 1-9 to 0
		if the slot has a 1, that indicates that the value
		has been used before, and therefore there is a duplicate*/
		for (i = 0; i <= 9; i++)
		{
			checker[i] = 0;
		}

		// For loop to go through the row
		for (i = 0; i < 9; i++)
		{
			/* Check to see if the current cell in the row is not 0
			meaning that there is data in the cell*/
			if (Board[row][i] != 0)
			{
				/* If there is data, then see if that space in the array is a 0 or 1
				i.e. if we are checking value 5, we look at location 5 of the checker vector
				if the value stored there is 1, then we have come across this value before
				and therefore, we have a duplicte. If not, then this is the first time we've come
				accross the value, so make the value 1 in the checker array.*/ 
				if (checker[Board[row][i]] == 1)
				{
					return false;
				}

				// If checker index is not equal to one, then set to one at this point
				checker[Board[row][i]] = 1;
			}
		}

		/* If we get to this point, we have successfully gone through the row and we have 
		found no duplicates, so return true.*/ 
		return true;
	}

	// validate_Column 
	bool validate_Column(int Column)
	{
		int i; // Local variables

		/* Clear the checker array slots 1-9 to 0
		if the slot has a 1, that indicates that the value
		has been used before, and therefore there is a duplicate*/
		for (i = 0; i <= 9; i++)
		{
			checker[i] = 0;
		}

		// For loop to go through the column
		for (i = 0; i < 9; i++)
		{
			/* Check to see if the current cell in the column is not 0
			meaning that there is data in the cell*/
			if (Board[i][Column] != 0)
			{
				/* If there is data, then see if that space in the array is a 0 or 1
				i.e. if we are checking value 5, we look at location 5 of the checker vector
				if the value stored there is 1, then we have come across this value before
				and therefore, we have a duplicte. If not, then this is the first time we've come
				accross the value, so make the value 1 in the checker vector.*/
				if (checker[Board[i][Column]] == 1)
				{
					return false;
				}

				// If checker index is not equal to one, then set to one at this point
				checker[Board[i][Column]] = 1;
			}
		}

		//if we get to this point, we have successfully gone through the column and we have 
		//found no duplicates, so return true. 
		return true;
	}

	// validate_Panel
	bool validate_Panel(int panelRow, int panelColumn)
	{
		/* You pass through the corner of the panel that needs to be validated
		this is calculated by r-r%3 and c-c%3 where r and c is the row and column
		that is located within a given panel on the board.*/
 
		int r, c, i; // Local variables

		/* Go through the checker array and set the values to 0 so we
		can check the values of the panel and ensure there are no duplicates*/ 
		for (i = 0; i <= 9; i++)
		{
			checker[i] = 0;
		}

		/* Set r to the current value of PanelRow (which should be the starting row
		of the panel we are verifying. We loop until r is less than the current
		value of the panelRow +3 (because the pannel has only 3 more rows.)*/
		for (r = panelRow; r < panelRow + 3; r++)
		{
			/* Set c to the current value of PanelColumn (which should be the starting row
			of the panel we are verifying. We loop until c is less than the current value
			of the panelColumn +3 (because the pannel has only 3 more columns.)*/

			/* Note that the combination of these two for statments will effectively 
			traverse the entire panel. We start with a single row, then go through all the columns
			then jump to the next row.*/ 
			for (c = panelColumn; c < panelColumn + 3; c++)
			{
				/* Check to see if the current value in the Board that we are at is not 0. 
				meaning it is empty.*/ 
				if (Board[r][c] != 0) {

					/* Take the value stored in the Board, then look at the index of the checker.
					i.e. if the value stored in the Board is 5, then we are looking in checker[5]
					then we check the contents to see if it is 1. 
					if that's true, then we return false b/c we have  a duplicate.*/
					if (checker[Board[r][c]] == 1)
					{
						return false;
					}

					// Otherwise, we set the value of the checker Board to 1. 
					checker[Board[r][c]] = 1;
				}
			}
		}

		// If we get to this point, then the panel is verified. 
		return true;
	}

	// solve Function
	bool solve(int row, int column)
	{
		int i; // Local variable

		// Traverse the Board until you find an empty cell. 
		while (row < 9 && Board[row][column] != 0)
		{
			column++;
			if (column == 9) {
				row++;
				column = 0;
			}
		}

		/* When you exit this part of the code, variables row and column will be 
		pointing at an empty cell (a cell filled with the value 0)*/

		// Base case of recursive function 
		if (row == 9) return 1;

		/* For statment that will go through and place the values 1-9 in the cell and test until 
		a value is found that satisfies all of the valdation functions.*/
		for (i = 1; i <= 9; i++)
		{
			// Insert the value into the cell we are looking at. 
			Board[row][column] = i;
			// Test to see if all the validation tests come back true.  
			if (validate_Row(row) &&
				validate_Column(column) &&
				validate_Panel(row - row % 3, column - column % 3) &&
				solve(row, column))
			{
				// If they do, then return true. 
				return true;
			}
			// Otherwise, loop again, and try the next value. 
		}

		/* If we get to this point, we have tried all values, and they have all failed.
		this means we cannot solve this problem. */
		Board[row][column] = 0;
		return false;
	}

	// print_Board Function
	void print_Board()
	{
		int row_row = 0; // Local variable

		cout << "\n\n|-----------------------------------------------------|" << endl;
		for (int i = 0; i < ROW; i++)
		{
			cout << "|     |     |     |     |     |     |     |     |     |" << endl;
			for (int j = 0; j < ROW; j++)
			{
				if (Board[i][j] == 0)
				{
					cout << "|  " << " " << "  ";
				}

				else
				{
					cout << "|  " << Board[i][j] << "  ";
				}
				
				row_row++;
			}
			cout << "|\n|     |     |     |     |     |     |     |     |     |" << endl;
			cout << "|-----------------------------------------------------|" << endl;
		}
	}

private:
	// Esablish local Variables
	int Board[ROW][ROW]; // Board 9x9
	int checker[ROW + 1]; // Single array x10
	int source[MAX]; // Single array x81
	int in_total = 0; // Counter for size of source array
};

