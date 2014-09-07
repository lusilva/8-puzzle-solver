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
	Board(const std::string &input) : input_string_(input) {}
	~Board() {
		this->destroy_board();
		this->board = NULL;
	}






private:
     
    /*   BOARD PROPERTIES   */
	const std::string input_string_;  // The input string given by the user.
	int** board_[3][3]       = NULL;  // Representation of a board.
	int moves_made_          = 0; 	  // Actual number of moves made so far.
	int est_moves_remaining_ = 0; 	  // Estimated moves remaining, using heuristic function.
	Board* previous_state_   = NULL;  // A pointer to the previous board state.

    /*   BOARD FUNCTIONS   */
    // Free dynamically allocated memory for board.
	void destroy_board();

};



#endif