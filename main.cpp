/////////////////////////////////////////////////
// Copyright 2014 Lucas Silva                  //
// The main file in the program                //
/////////////////////////////////////////////////

#include <iostream>

#include "headers/board.h"

int main() {
    Board board = Board("0 1 2 3 4 5 6 7 8");
    std::cout << board.GetInputString() << std::endl;
    if (board.CreateBoard()) {
        std::cout << "Hello!" << std::endl;
    }
    return 1;
}
