/////////////////////////////////////////////////
// Copyright 2014 Lucas Silva                  //
// The main file in the program                //
/////////////////////////////////////////////////

// TODO(Lucas): Implement priority queue and A*
// TODO(lucas): Implement IO

#include <iostream>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector

#include "headers/board.h"

/**
 * The class used to compare the board pointers in the priority queue.
 * This is just used since the less than operator cannot handle comparing pointers,
 * so this just dereferences the pointers and pass them into the overloaded
 * less than operator. All logic is inside the operator.
 */
class QueueCompareClass {
 public:
    bool operator() (const Board* rhs, const Board* lhs) {
        return *rhs < *lhs;
    }
};

void MoveAllDirectionsAndAddToQueue(const Board* board,
    std::priority_queue<Board*, std::vector<Board*>, QueueCompareClass> &queue) {

    Board* board_right = new Board(*board);
    Board* board_left = new Board(*board);
    Board* board_up = new Board(*board);
    Board* board_down = new Board(*board);
}

///////////////////
// Start of main //
///////////////////

int main() {
    std::priority_queue<Board*, std::vector<Board*>, QueueCompareClass> pq;

    Board* board = new Board("1 0 2 3 4 5 6 7 8");
    if (board->CreateBoard()) {
        pq.push(board);
        board->PrintBoard();
        std::cout << board->GetHeuristicValue() << std::endl;
    }
    Board* new_board = new Board(*board);

    new_board->MoveRight();
    pq.push(new_board);
    std::cout << "OLD BOARD" << std::endl;
    board->PrintBoard();
    std::cout << "OLD BOARD RANK: " << board->GetRank() << std::endl;
    std::cout << "NEW BOARD" << std::endl;
    new_board->PrintBoard();
    std::cout << "NEW BOARD RANK: " << new_board->GetRank() << std::endl;

    std::cout << "FIRST POP" << std::endl;
    pq.top()->PrintBoard();

    delete board;
    delete new_board;
    return 0;
}
