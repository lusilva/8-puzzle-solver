Lucas Silva
Intro to AI - Assignment 1
Due Date: Sunday, September 28 by 11:59PM


This is a solver for the 8-puzzle problem, using the A* algorithm with 
a manhattan distance heuristic. The program does not check for 
invalid boards, so input boards must be solvable, as defined in the 
assignment pdf.

File structure:
    This assignment is broken up into three files:
        - main.cpp: actually implements the A* algorithm and handles input/output
        - board.h: header file for the board class, contains all method declarations 
        and comments on what they do.
        - board.cpp: implementation file for the board class, contains the 
        method definitions. Most of the functionality of moving the board and 
        calculating value on the priority queue is done from within this class.

How to use:
    Once run, the program will print out directions and then expects the user to input a 
    string representing a linearlized board. 
    
    For example:
    -----------
    | 1  4  2 |
    | 3     5 |
    | 6  7  8 |
    -----------
    to get the board above the user would enter '1 4 2 3 0 5 6 7 8' 
    (without quotations, and with or without spaces)

    The program then calculates the manhattan distance from the initial board
    to both of the valid goal states, blank at top left and at bottom right, 
    and picks whatever state yields a lower heuristic value.

    Once solved, a step by step solution is printed out to std::cout



