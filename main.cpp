/////////////////////////////////////////////////
// Copyright 2014 Lucas Silva                  //
// The main file in the program                //
/////////////////////////////////////////////////

// TODO(Lucas): Implement priority queue and A*
// TODO(lucas): Implement IO

#include <iostream>

#include "headers/board.h"

int main() {
    Board* board = new Board("1 0 2 3 4 5 6 7 8");
    if (board->CreateBoard()) {
        board->PrintBoard();
        std::cout << board->GetHeuristicValue() << std::endl;
    }
    Board* new_board = new Board(*board);

    new_board->MoveRight();
    std::cout << "OLD BOARD" << std::endl;
    board->PrintBoard();
    std::cout << "NEW BOARD" << std::endl;
    new_board->PrintBoard();
    new_board->GetPreviousState()->PrintBoard();

    delete board;
    delete new_board;
    return 1;
}
