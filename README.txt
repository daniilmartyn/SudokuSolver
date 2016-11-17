Daniil Martyn
daniil.martyn@email.wsu.edu

File in Archive:
	README.txt (this file)
	SudokuGrid.h
	sudokusover.cpp
	makefile
	simple.txt
	hard.txt
	
Brief Description:
	This project is a sudoku puzzle solver. It takes an input string that represents the initial state of
	the puzzle and prints out the solution by using backtracking. Before applying the backtracking method, it
	attempts to solve as much of the puzzle as possible by looking for "naked singles" as described at
		http://www.sudokuwiki.org/Naked_Candidates
	More information about backtracking can be found in the following video:
		 https://youtu.be/p-gpaIGRCQI
	
How to build/run:
	The source code of the solvesudoku program is written in C++11 and requires the appropriate compiler to
	build the program (g++ 4.7 or later, or clang++). To build the program, unzip (or untar) all files into one 
	directory. Using a command prompt or terminal execute the "make" command. This should build all the necessary
	files for the program as well as the final executable program named solvesudoku. Example:
		
		make 			#builds the solvesudoku program
		make clean		#removes all the intermediate build files, but not the solvesudoku executable
		
	To run the program, execute the solvesudoku program from the command line using ./solvesudoku
	This command starts the program and the program waits for input from stdin. The input is an 81 character
	string of digits (1-9) and dots that represent the sudoku puzzle in row-major order. The digits represent
	the initial numbers and the dots represent the empty spaces. You man either type in the 81 character 
	string by hand, copy and paste the string or pass in the string using pipes. Two files have been provided:
	simple.txt and hard.txt. Both files contain a large list of sudoku puzzle strings. To choose a string from
	a file to be used by solvesudoku use the following command:
		
		sed -n "10p" hard.txt | ./solvesudoku
	
	the "10p" represents the line number in the file "hard.txt". The 10 can be replaces with any available line 
	number, and the hard.txt file can be replaced with simple.txt or any other file with valid sudoku puzzle strings.
	The sed command passes a sudoku puzzle string to solvesudoku, and solvesudoku pretty prints the original puzzle,
	a puzzle with deduced numbers, and finally the solved puzzle. On modern machines, this process should take no longer
	than 30 seconds.
	
Issues:
	There doesn't seem to be any obvious issues with the program.
	
	If an incorrect string is supplied to the solver,
	the program should exit with an error message. However, all possible inputs have not been tests
	so it is possible something may break the solver.
	
	Extremely difficult puzzles may take a very long time to solve.