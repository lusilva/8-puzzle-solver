/////////////////////////////////////////////////
// Copyright 2014 Lucas Silva                  //
// The main file in the program                //
/////////////////////////////////////////////////

// TODO(lucas): Implement IO

#include <iostream>
#include <queue>          // std::priority_queue
#include <vector>         // std::vector
#include <utility>

#include "headers/board.h"

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

const unsigned int DIRECTIONS[4] = {RIGHT, LEFT, UP, DOWN};

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

/**
 * Determines if a move can be made in the specified direction.
 * @param  direction One of the four directions.
 * @param  board The board to be checked.
 * @return true if a move in that direction is possible.
 */
bool CanMoveInDirection(int direction, Board* &board) {
    switch (direction) {
        case RIGHT:
            return board->CanMoveRight();
        case LEFT:
            return board->CanMoveLeft();
        case UP:
            return board->CanMoveUp();
        case DOWN:
            return board->CanMoveDown();
    }
}

/**
 * Moves the given board in the given direction
 * @param direction The direction to move in.
 * @param board     The board to be moved.
 */
bool MoveInDirection(int direction, Board* &board) {
    switch (direction) {
        case RIGHT:
            board->MoveRight();
            break;
        case LEFT:
            board->MoveLeft();
            break;
        case UP:
            board->MoveUp();
            break;
        case DOWN:
            board->MoveDown();
            break;
    }
    return true;
}

/**
 * Moves a board in all the possible directions and adds the new states to the queue.
 * @param board The board to be moved.
 * @param queue The priority queue holding all board states.
 */
std::pair<bool, Board*> MoveAllDirectionsAndAddToQueue(Board* &board,
    std::priority_queue<Board*, std::vector<Board*>, QueueCompareClass> &queue) {

    // For all 4 directions, try to move in that direction.
    for (unsigned int i = 0; i < 4; ++i) {
        int direction = DIRECTIONS[i];
        // If the board can move in that direction, then move it.
        // If it can't, then do nothing.
        if (CanMoveInDirection(direction, board)) {
            // Create a copy of the current board, and move the copy.
            Board* new_board = new Board(*board);
            // Actually move the board.
            MoveInDirection(direction, new_board);
            // Set the previous board state.
            new_board->SetPreviousState(board);
            // Check if the board is at the goal state, if so then stop.
            if (new_board->IsAtGoalState()) {
                return std::make_pair(true, new_board);
            }
            // Do not add the new state to the queue if the new board is the
            // same as the previous state.
            if (board->GetPreviousState() &&
                *(board->GetPreviousState()) == *new_board) {
                delete new_board;
                new_board = NULL;
            } else {
                queue.push(new_board);
            }
        }
    }

    return std::make_pair(false, reinterpret_cast<Board*>(NULL));
}

Board* Solve(std::priority_queue<Board*, std::vector<Board*>,
    QueueCompareClass> &pq, std::vector<Board*> &to_delete) {
    // While the board isn't empty, try to find the solution.
    while (!pq.empty()) {
        // Get the board with least rank from the top of the queue.
        // Rank = moves made so far + estimated number of moves remaining
        Board* board = pq.top();

        // Move in all directions, adding the boards to the queue.
        std::pair<bool, Board*> result =
          MoveAllDirectionsAndAddToQueue(board, pq);

        // If the goal state has been reached, then we are done!
        if (result.first) {
            return result.second;
        }
        
        pq.pop();
        to_delete.push_back(board);

    }

    // No goal state was found!
    reinterpret_cast<Board*>(NULL);
}

void Cleanup(std::priority_queue<Board*, std::vector<Board*>,
    QueueCompareClass> &pq, std::vector<Board*> to_delete) {

    for (unsigned int i = 0; i < to_delete.size(); ++i) {
        delete to_delete[i];
        to_delete[i] = NULL;
    }

    while (!pq.empty()) {
        Board* board = pq.top();
        pq.pop();
        delete board;
        board = NULL;
    }
}

///////////////////
// Start of main //
///////////////////

int main() {
    // The priority queue to hold all the board states.
    std::priority_queue<Board*, std::vector<Board*>, QueueCompareClass> pq;

    std::vector<Board*> to_delete;

    // Create a board object from the input string.
    Board* board = new Board("4 7 2 5 8 1 3 6 0");
    if (board->CreateBoard()) {
        // Add the board to the queue.
        pq.push(board);
        std::cout << "Pushed initial board" << std::endl;
        board->PrintBoard();
    } else {
        std::cerr << "Board could not be created!" << std::endl;
        return 1;
    }

    Board* answer = Solve(pq, to_delete);
    if (!answer) {
        std::cout << "COULD NOT FIND SOLUTION" << std::endl;
        return 1;
    }

    answer->DisplayAllSteps();

    Cleanup(pq, to_delete);


    return 0;
}
