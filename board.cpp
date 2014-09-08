/////////////////////////////////////////////////
// Copyright 2014 Lucas Silva                  //
// The implementation file for the board class //
/////////////////////////////////////////////////

#include "headers/board.h"

/**
 * Deallocates dynamic memory used to store the board.
 * @private
 */
Board::destroy_board_() {
    if (this->memory_allocated_) {
        for ( int i = 0; i < 3; ++i ) {
            delete [] this->board_[i];
        }
        delete [] this->board_;
    }
}
