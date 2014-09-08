/////////////////////////////////////////////////
// Copyright 2014 Lucas Silva                  //
// The implementation file for the board class //
/////////////////////////////////////////////////

#include "headers/board.h"

/*
 * Allocates memory and initializes the board. 
 * Must be called after making a new board instance.
 * @return {boolean} true if allocation successful, false otherwise.
*/
bool Board::CreateBoard() {
    try {
        this->board_ = new int*[3];
        for (int i = 0; i < 3; ++i)
            this->board_[i] = new int[3];
    }
    catch(std::bad_alloc exc) {
        return false;
    }
}

/*
 * Calculates the sum of all manhattan distances of every piece on the board.
 * This is the heuristic function used for the A* algorithm.
 */
int Board::SumManhattanDistances() {
    int manhattanDistanceSum = 0;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
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
