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
    explicit Board(const std::string &input) : input_string_(input) {}

    /*
     * Destructor for the Board class. Deallocates dyanmically created memory.
     */
    ~Board() {
        this->destroy_board();
        this->board = NULL;
    }



 private:
    /* The input string given by the user. */
    const std::string input_string_;
    /* Flag to store when memory is allocated. */
    bool memory_allocated_   = false;
    /* Representation of a board as a dynamically allocated 2-D array */
    int** board_[3][3]       = NULL;
    /* Actual number of moves made so far */
    int moves_made_          = 0;
    /* Estimated moves remaining, using heuristic function. */
    int est_moves_remaining_ = 0;
    /* A pointer to the previous board state. */
    Board* previous_state_   = NULL;

    /* Free dynamically allocated memory for board. */
    void destroy_board();
};



#endif
