/////////////////////////////////////////////////
// Copyright 2014 Lucas Silva                  //
// The implementation file for the board class //
/////////////////////////////////////////////////

#include "headers/board.h"

/**
  * Allocates memory and initializes the board. 
  * Must be called after making a new board instance.
  * @return {boolean} true if allocation successful, false otherwise.
  */
bool Board::CreateBoard() {
    if (!this->AllocateBoard_()) {return false;}
    if (this->input_string_.length() != 9) {
        std::cerr << "ERROR: Invalid input. Need 9 tiles.";
        return false;
    }
    for (int tile = 0; tile < this->input_string_.length(); tile++) {
        this->board_[tile/3][tile%3] = this->input_string_[tile];
    }
}

/**
  * Calculates the sum of all manhattan distances of every piece on the board.
  * This is the heuristic function used for the A* algorithm.
  */
int Board::SumManhattanDistances() {
    int manhattanDistanceSum = 0;
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            int value = this->board_[x][y];
            if (value != 0) {
                int targetX = (value) / 3;
                int targetY = (value) % 3;
                int dx = x - targetX;
                int dy = y - targetY;
                manhattanDistanceSum += std::abs(dx) + std::abs(dy);
            }
        }
    }
}

//////////////////////////////
// Private helper functions //
//////////////////////////////

/**
 * Deallocates dynamic memory used to store the board.
 * @private
 */
void Board::DestroyBoard_() {
    if (this->memory_allocated_) {
        for (int i = 0; i < 3; ++i) {
            delete [] this->board_[i];
        }
        delete [] this->board_;
        this->memory_allocated_ = false;
    }
}

/**
 * Allocate dynamic memory used to store the board.
 * @private
 * @return {boolean} true if allocation successful, false otherwise.
 */
bool Board::AllocateBoard_() {
    if (memory_allocated_) {
        std::cerr << "ERROR: Memory has already been allocated";
        return false;
    }
    try {
        this->board_ = new int*[3];
        for (int i = 0; i < 3; ++i)
            this->board_[i] = new int[3];
        this->memory_allocated_ = true;
        return true;
    }
    catch(std::bad_alloc exc) {
        std::cerr << "ERROR: Memory allocation failed";
        return false;
    }
}
