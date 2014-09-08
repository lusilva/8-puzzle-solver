/////////////////////////////////////////
// Copyright 2014 Lucas Silva          //
// The header file for the board class //
/////////////////////////////////////////

#ifndef _board_h
#define _board_h

#include <iostream>
#include <string>

/*
	The board class stores the states of the board and provides a way to interact with 
	the board by making moves.
*/
class Board {
 public:
 	/*
 	 * Constructor for the Board class. 
 	 * @param {string} input The user input
 	 */
    explicit Board(const std::string &input) : input_string_(input),
      memory_allocated_(false), moves_made_(0),
      est_moves_remaining_(0), previous_state_(NULL) {}

    /*
     * Destructor for the Board class. Deallocates dyanmically created memory.
     */
    ~Board() {this->DestroyBoard_();}

    /**
     * Gets the input string used to create the table.
     * @return {string} the input string
     */
    std::string GetInputString() {return this->input_string_;}

    /*
     * Allocates memory and initializes the board. 
     * Must be called after making a new board instance.
     * @return {boolean} true if allocation successful, false otherwise.
     */
    bool CreateBoard();

    /*
     * Calculates the sum of all manhattan distances of every piece on the board.
     * This is the heuristic function used for the A* algorithm.
     */
    int SumManhattanDistances();



 private:
    /* The input string given by the user. */
    const std::string input_string_;
    /* Flag to store when memory is allocated. */
    bool memory_allocated_;
    /* Representation of a board as a dynamically allocated 2-D array */
    int** board_;
    /* Actual number of moves made so far */
    int moves_made_;
    /* Estimated moves remaining, using heuristic function. */
    int est_moves_remaining_;
    /* A pointer to the previous board state. */
    Board* previous_state_;

    /* Free dynamically allocated memory for board. */
    void DestroyBoard_();

    /* Allocates dynamic memory used to store the board. */
    bool AllocateBoard_();

    /* Removes all spaces from input string */
    std::string TrimSpaceFromInputString();
};



#endif
