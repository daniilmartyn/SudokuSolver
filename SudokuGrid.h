#ifndef SUDOKU_GRID_H
#define SUDOKU_GRID_H

#include <iostream>
#include <string>
#include <array>
#include <bitset>

class SudokuGrid{
private:
	struct Cell{
		int number;
		bool fixed;
		bool solved;
		std::bitset<9> pencils;
	};
	std::array<std::array<Cell,9>,9> grid;
	
public:
	
	SudokuGrid(std::string s){
		int k = 0;
		for(int i = 0; i < 9; i++){
			for(int j = 0; j < 9; j++){
				if(s[k] == '.'){
					grid[i][j].number = 0;
					grid[i][j].fixed = false;
					grid[i][j].solved = false;
				}else{
					const char idk [2] = { s[k], '\0'};
					const int val = std::stoi(idk);
					grid[i][j].number = val;
					grid[i][j].fixed = true;
					grid[i][j].solved = true;
				}
				k++;
			}
		}
		std::cout << "\n";
	}
	
	int number( int row, int col) const{
		return grid[row][col].number;
	}
	
	void setNumber(int row, int col, int num){
		grid[row][col].number = num;
	}
	
	bool isFixed(int row, int col) const{
		return grid[row][col].fixed;
	}
	
	bool isSolved( int row, int col) const{
		return grid[row][col].solved;
	}
	
	void setSolved(int row, int col){
		grid[row][col].solved = true;
	}
	
	bool isPencilSet(int row, int col, int n) const{
		return grid[row][col].pencils.test(n-1);
	}
	
	bool anyPencilsSet(int row, int col) const{
		return grid[row][col].pencils.any();
	}
	
	void setPencil(int row, int col, int n){
		grid[row][col].pencils[n-1] = 1;
	}
	
	void setAllPencils(int row, int col){
		grid[row][col].pencils.set();
	}
	
	void clearPencil(int row, int col, int n){
		grid[row][col].pencils[n-1] = 0;
	}
	
	void clearAllPencils(int row, int col){
		grid[row][col].pencils.reset();
	}
	
	~SudokuGrid(){}
};

#endif