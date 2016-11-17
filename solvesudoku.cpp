//Daniil Martyn
#include <iostream>
#include "SudokuGrid.h"


bool conflictingNumber(SudokuGrid& grid, int r, int c, int n){
	
	for(int i = 0; i < 9; i++){ // check for conflicting number in row
		if(grid.number(r,i) == n)
			return true;
	}
	
	for(int j = 0; j < 9; j++){ // check for conflicting number in column
		if(grid.number(j,c) == n)
			return true;
	}
	
	int blockR = r/3 *3;
	int blockC = c/3 *3;
	
	for(int i = blockR; i < blockR + 3; i++){
		for(int j = blockC; j < blockC +3; j++){
			if(grid.number(i,j) == n)
				return true;
		}
	}
	
	return false;
}

int numPencilsInRow(SudokuGrid& grid, int row, int n){
	int num = 0;
	
	for(int i = 0; i < 9; i++){
		if(grid.isPencilSet(row,i,n))
			num++;
	}
	
	return num;
}

int numPencilsInColumn(SudokuGrid& grid, int col, int n){
	int num = 0;
	
	for(int i = 0; i < 9; i++){
		if(grid.isPencilSet(i,col,n))
			num++;
	}
	
	return num;
}

int numPencilsInBlock(SudokuGrid& grid, int row, int col, int n){
	int num = 0;
	
	int blockR = row/3 *3;
	int blockC = col/3 *3;

	for(int i = blockR; i < blockR + 3; i++){
		for(int j = blockC; j < blockC + 3; j++){
			if(grid.isPencilSet(i,j,n))
				num++;
		}
	}
	
	return num;
}

bool findUnassignedLocation(SudokuGrid& grid, int& row, int& col){
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(grid.number(i,j) == 0){
				row = i;
				col = j;
				return true;
			}
		}
	}
	
	return false;
}


void autoPencil(SudokuGrid& grid) {
	for (int r = 0; r < 9; r++)
		for (int c = 0; c < 9; c++)
			if (grid.number(r,c) == 0) {
				grid.setAllPencils(r,c);
				for (int n = 1; n <= 9; n++)
					if (conflictingNumber(grid,r,c,n))
						grid.clearPencil(r,c,n);
			}
}

void deduce(SudokuGrid& grid) {
	bool changed;
	do { // repeat until no changes made
		autoPencil(grid);
		changed = false;
		for (int row = 0; row < 9; row++)
			for (int col = 0; col < 9; col++)
				for (int n = 1; n <= 9; n++)
					if (grid.isPencilSet(row, col, n) &&
					 (numPencilsInRow(grid, row, n) == 1 ||
					  numPencilsInColumn(grid, col, n) == 1 ||
					  numPencilsInBlock(grid, row, col, n) == 1)) {
						grid.clearAllPencils(row, col);
						grid.setNumber(row,col,n);
						grid.setSolved(row,col);
						changed = true;
						break;
					}
	} while(changed);
}


bool solveSudoku(SudokuGrid& grid) {
	int row, col;
	if (!findUnassignedLocation(grid, row, col))
		return true; // puzzle filled, solution found!
	for (int num = 1; num <= 9; num++)
		if (!conflictingNumber(grid, row, col, num)) {
			grid.setNumber(row, col, num); // try next number
			if (solveSudoku(grid))
				return true; // solved!
			grid.setNumber(row, col, 0); // not solved, clear number
		}
	return false; // not solved, back track
}

bool isStringOk(std::string puzzle){
	if(puzzle.length() != 81){
		return false;
	}
	for(unsigned int i = 0; i < puzzle.length(); i++){
		if((puzzle[i] != '.') && !isdigit(puzzle[i])){
			return false;
		}
	}
	return true;
}

void printPuzzle(SudokuGrid& grid){
	
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			if(j == 3 || j== 6 || j==9)
				std::cout << "| ";
			if(grid.number(i,j) == 0){
				std::cout << ". ";
			}else{
				std::cout << grid.number(i,j) << " ";
			}
		}
		std::cout << "\n";
		if(i == 2 || i == 5)
			std::cout << "------+-------+------\n";
	}
	
}

int main(){
	std::string puzzle;
	std::cin >> puzzle;
	
	if(!isStringOk(puzzle)){
		std::cerr << "Error: Input string is not 81 characters long or not made of digits and dots\n";
		exit(1);
	}
	
	SudokuGrid grid(puzzle);
	printPuzzle(grid);
	std::cout << "\n";
	
	deduce(grid);
	printPuzzle(grid);
	std::cout << "\n";
	
	solveSudoku(grid);
	printPuzzle(grid);
	
	return 0;
}