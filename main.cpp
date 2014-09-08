/////////////////////////////////////////////////
// Copyright 2014 Lucas Silva                  //
// The main file in the program                //
/////////////////////////////////////////////////

#include <iostream>

#include "headers/board.h"

int main() {
    Board board = Board("1 0 2 3 4 5 6 7 8");
    if (board.CreateBoard()) {
        board.PrintBoard();
        std::cout << board.GetHeuristicValue() << std::endl;
    }
    return 1;
}
