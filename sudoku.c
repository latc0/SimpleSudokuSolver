/*
SimpleSudokuSolver
Copyright (C) 2015  Sam Wilberforce <git@samwilberforce.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include "sudoku.h"

int main(int argc, char *argv[]) {

	sudokuGrid sample = {
		1,3,0,0,0,0,0,5,0,
		0,0,0,0,0,0,2,0,8,
		0,8,4,7,9,0,0,0,0,
		2,0,1,0,8,0,4,3,0,
		0,5,0,0,0,0,0,8,0,
		0,6,9,0,2,0,5,0,1,
		0,0,0,0,3,6,8,2,0,
		6,0,7,0,0,0,0,0,0,
		0,2,0,0,0,0,0,1,5
	};
	printf("\nInput\n");
	showGame(sample);
	printf("Finding solution..\n");

	if (hasSolution(sample)) {
		printf("Got solution!\n");
		showGame(sample);
	}
	else {
		printf("\nNo solution :(\n");
		showGame(sample);
	}
	return 0;
}

int hasSolution(sudokuGrid game) {
	if (isFull(game)) {
		return TRUE;
	}
	else {
		cell candidateCell = getEmptyCell(game);
		value trialValue = MIN_VAL;
		int solved = FALSE;

		while (!solved && (trialValue <= MAX_VAL)) {
			if (isLegal(game, candidateCell, trialValue)) {
				setCell(game, candidateCell, trialValue);
				if (hasSolution(game) == TRUE) {
					return TRUE;
				}
				else {
					clearCell(game, candidateCell);
				}
			}
			trialValue++;
		}
		return solved;
	}
}

int isLegal(sudokuGrid game, cell candidateCell, value trialValue) {

	// check the column
	int column = candidateCell % 9;//remainder
	int rowAdd = 0;
	while (rowAdd <= MAX_CELL)
	{
		if (game[column + rowAdd] == trialValue)
			return FALSE;
		rowAdd += 9;
	}

	// check the row
	int rowStartIndex = candidateCell - column; //row start index

	// loop through each cell in the row to check whether value already exists
	for (int i = 0; i < NUM_VALUES; i++) {
		if (game[rowStartIndex + i] == trialValue) {
			return FALSE;
		}
	}

	//check box
	int horBox = column - (column % 3);//gives 0,3 or 6 - column index of left of box
	int row = rowStartIndex / 9;//get actual row index of candidate
	int vertBox = row - (row % 3);//0,3 or 6 - row index of top of box

	//get index of cell in top left of relevant box
	int startCell = (vertBox * 9) + horBox;

	//check digits in box
	for (int r = 0; r <= 2; r++) {
		for (int c = startCell; c <= startCell + 2; c++) {
			//int look = startCell + c;
			if (game[c] == trialValue) {
				return FALSE;
			}
		}
		startCell += 9;//go to next row
	}

	return TRUE;
}

int isFull(sudokuGrid game) {
	for (int i = 0; i <= MAX_CELL; i++) {
		if (game[i] == 0)
			return FALSE;
	}
	return TRUE;
}

void clearCell(sudokuGrid game, cell location) {
	game[location] = EMPTY;
}

void setCell(sudokuGrid game, cell location, value digit) {
	game[location] = digit;
}

cell getEmptyCell(sudokuGrid game) {
	for (int i = 0; i < GRID_SIZE; i++) {
		if (game[i] == EMPTY)
			return i;
	}
}

void printLines() {
	for (int i = 0; i < 9; i++) {
		if (i % 3 == 0)printf("| ");
		//else
		printf("- ");
	}
	printf("|\n");
}

void showGame(sudokuGrid game) {
	printf("\n");
	for (int i = 0; i < 9; i++) {
		if (i % 3 == 0 && i != 0)printLines();
		for (int j = 0; j < 9; j++) {
			if (j % 3 == 0)printf("| ");
			printf("%i ", game[(9 * i) + j]);
			if (j == 8)printf("|");
		}
		printf("\n");
	}
	printf("\n");
}