#include "board.h"

Board::destroy_board() {
	for(int i = 0; i < 3; ++i) {
		delete [] this->board_[i];
	}
	delete [] this->board_;
}