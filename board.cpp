/////////////////////////////////////////////////
// Assignment 1 : Lucas Silva                  //
// The implementation file for the board class //
/////////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <cassert>
#include <vector>

#include "headers/board.h"

#define RIGHT 1           // Represents a move to the right
#define LEFT 2            // Represents a move to the left
#define UP 3              // Represents a move up
#define DOWN 4            // Represents a move down
#define TOP_LEFT 5        // Represents a goal state with empty space at top left
#define BOTTOM_RIGHT 6    // Represents a goal state with empty space at bottom right

/**
 * Copy constructor for the board class.
 * @param {Board} the board to be copied
 */
Board::Board(const Board& board) {
    assert(board.IsValid());

    try {
        this->board_ = new int*[3];
        for (int i = 0; i < 3; ++i)
            this->board_[i] = new int[3];
    }
    catch(std::bad_alloc exc) {
        std::cerr << "ERROR: Memory allocation failed" << std::endl;
        exit(1);
    }

    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            this->board_[x][y] = board.GetValueAt(x, y);
        }
    }
    this->empty_space_position_ = board.empty_space_position_;
    this->moves_made_ = board.moves_made_;
    this->estimated_moves_remaining_ = board.estimated_moves_remaining_;
    this->previous_state_ = NULL;
    this->goal_state_type_ = board.goal_state_type_;

    assert(this->board_);
}


/**
 * Returns the value of the tile at board[x][y].
 * Retuns -1 if board hasn't been initialized yet.
 * @param {int} x The x coordinate of the point. 
 * @param {int} y The y coordinate of the point.
 * @return {int} The value of the tile at those coordinates.
 */
const int Board::GetValueAt(int x, int y) const {
    if (!this->board_) {
        std::cerr << "ERROR: Board has not been initialized yet.\n";
        exit(1);
    }
    if (x > 2 || x < 0 || y > 2 || y < 0) {
        std::cerr << "ERROR: Coordinates out of range. \n";
        exit(1);
    }
    return this->board_[x][y];
}

/**
 * Checks if a board has been allocated and initialized.
 * @return {boolean} true if board is valid.
 */
bool Board::IsValid() const {
    if (!this) {
        return false;
    }
    if (!this->board_) {
        return false;
    }
    return true;
}

/**
  * Allocates memory and initializes the board. 
  * Must be called after making a new board instance.
  * @return {boolean} true if allocation successful, false otherwise.
  */
bool Board::CreateBoard() {
    // Try to allocate board, if it fails then return false.
    if (!this->AllocateBoard_()) {return false;}
    // Make sure input string is valid.
    std::string input = this->TrimSpaceFromInputString_();
    if (input.length() != 9) {
        std::cerr << "ERROR: Invalid input. Need 9 tiles." << std::endl;
        this->DestroyBoard_();
        return false;
    }
    // Array used to check for duplicate numbers. All entries
    // are initialized to zero, and as the numbers are read their 
    // index in the array is made true.
    bool check_for_duplicates_array[9];
    for (int i = 0; i < 9; ++i) {
        check_for_duplicates_array[i] = false;
    }

    // Actually fill in the tile values.
    for (int tile = 0; tile < input.length(); tile++) {
        // Convert the char to int and set it to that position in board.
        int tile_number = input[tile] - '0';
        if (tile_number < 0 || tile_number > 8) {
            std::cerr << "ERROR: Tiles are only valid in range 0-8 \n";
            this->DestroyBoard_();
            return false;
        }
        // Check for duplicate numbers.
        if (check_for_duplicates_array[tile_number]) {
            std::cerr << "ERROR: Tiles must be unique! \n";
            this->DestroyBoard_();
            return false;
        }
        check_for_duplicates_array[tile_number] = true;
        this->board_[tile/3][tile%3] = tile_number;
        // If this is the empty space, store its current position on the board.
        if (tile_number == 0) {
            this->empty_space_position_ = std::make_pair(tile/3, tile%3);
        }
    }
    // Determine if goal state should be with blank space
    // at the top left or at the bottom right, depending
    // on whichever one has a lower heuristic value.
    this->DetermineGoalState_();

    this->CalculateAndSetHeuristic_();
    return true;
}

/**
 * Prints the board,
 */
void Board::PrintBoard() const {
    // If the board hasn't been allocated, then can't print it.
    if (!this->board_) {
        std::cerr << "ERROR: Please make sure CreateBoard has been called.";
        std::cerr << std::endl;
        return;
    }
    std::cout << "-----------" << std::endl;
    for (int x = 0; x < 3; ++x) {
        std::cout << "|";
        for (int y = 0; y < 3; ++y) {
            std::cout << " ";
            if (this->board_[x][y] == 0) {
                std::cout << " ";
            } else {
                std::cout << this->board_[x][y];
            }
            std::cout << " ";
        }
        std::cout << "|\n";
    }
    std::cout << "-----------" << std::endl;
}

/**
 * Displays all the previous board states, in order.
 */
void Board::DisplayAllSteps() {
    // Vector to hold all the board states
    std::vector<Board*> all_boards;

    // Add all the board states to the vector, in reverse order.
    Board* board = this;
    while (board) {
        all_boards.push_back(board);
        board = board->GetPreviousState();
    }

    // Quick check to make sure the size of the vector is correct.
    assert(all_boards.size() == this->moves_made_ + 1);

    int number_of_boards = all_boards.size() - 1;
    for (int i = number_of_boards; i > -1; --i) {
        assert(all_boards[i]->IsValid());

        if (number_of_boards - i == 0) {
            std::cout << "INITIAL BOARD" << std::endl;
        } else if (i == 0) {
            std::cout << "GOAL STATE" << std::endl;
        } else {
            std::cout << "MOVE: " << all_boards[i]->GetMovesMade() << " - ";

            // Print out the direction of the move
            switch (all_boards[i]->direction_moved_) {
                case RIGHT:
                    std::cout << "moved right" << std::endl;
                    break;
                case LEFT:
                    std::cout << "moved left" << std::endl;
                    break;
                case UP:
                    std::cout << "moved up" << std::endl;
                    break;
                case DOWN:
                    std::cout << "moved down" << std::endl;
                    break;
            }
        }
        all_boards[i]->PrintBoard();
        std::cout << std::endl;
    }
}

/**
 * Gets the value of the heuristic function.
 * @return {int} The sum of the manhattan distances of all the tiles.
 */
int Board::GetHeuristicValue() {
    if (!this->board_ || this->estimated_moves_remaining_ == -1) {
        std::cerr << "No board. Please make sure CreateBoard has been called.";
        std::cerr << std::endl;
        return -1;
    }
    return this->CalculateAndSetHeuristic_();
}


/**
 * Determine whether a move to the right is possible.
 * @return {boolean} true if possible.
 */
bool Board::CanMoveRight() const {
    if (this->GetEmptySpaceColumn() >= 2) {
        return false;
    }
    return true;
}


/**
 * Moves the empty space to the right.
 * @return {boolean} true if the move was successful, false otherwise.
 */
bool Board::MoveRight() {
    if (!this->CanMoveRight()) {
        return false;
    }
    this->Move_(RIGHT);
    this->direction_moved_ = RIGHT;
    return true;
}

/**
 * Determine whether a move to the left is possible.
 * @return {boolean} true if possible.
 */
bool Board::CanMoveLeft() const {
    if (this->GetEmptySpaceColumn() <= 0) {
        return false;
    }
    return true;
}

/**
 * Moves the empty space to the left.
 * @return {boolean} true if the move was successful, false otherwise.
 */
bool Board::MoveLeft() {
    if (!this->CanMoveLeft()) {
        return false;
    }
    this->Move_(LEFT);
    this->direction_moved_ = LEFT;
    return true;
}

/**
 * Determine whether a move down is possible.
 * @return {boolean} true if possible.
 */
bool Board::CanMoveDown() const {
    if (this->GetEmptySpaceRow() >= 2) {
        return false;
    }
    return true;
}

/**
 * Moves the empty space down.
 * @return {boolean} true if the move was successful, false otherwise.
 */
bool Board::MoveDown() {
    if (!this->CanMoveDown()) {
        return false;
    }
    this->Move_(DOWN);
    this->direction_moved_ = DOWN;
    return true;
}

/**
 * Determine whether a move up is possible.
 * @return {boolean} true if possible.
 */
bool Board::CanMoveUp() const {
    if (this->GetEmptySpaceRow() <= 0) {
        return false;
    }
    return true;
}

/**
 * Moves the empty space up.
 * @return {boolean} true if the move was successful, false otherwise.
 */
bool Board::MoveUp() {
    if (!this->CanMoveUp()) {
        return false;
    }
    this->Move_(UP);
    this->direction_moved_ = UP;
    return true;
}

//////////////////////////////
// Private helper functions //
//////////////////////////////

/**
 * Deallocates dynamic memory used to store the board.
 * @private
 */
void Board::DestroyBoard_() {
    if (this->board_) {
        for (int i = 0; i < 3; ++i) {
            delete [] this->board_[i];
            this->board_[i] = NULL;
        }
        delete [] this->board_;
        this->board_ = NULL;
    }
}

/**
 * Allocate dynamic memory used to store the board.
 * @private
 * @return {boolean} true if allocation successful, false otherwise.
 */
bool Board::AllocateBoard_() {
    // Check if memory has already been allocated.
    if (this->board_) {
        std::cerr << "ERROR: Memory has already been allocated" << std::endl;
        return false;
    }
    try {
        this->board_ = new int*[3];
        for (int i = 0; i < 3; ++i)
            this->board_[i] = new int[3];
        return true;
    }
    catch(std::bad_alloc exc) {
        std::cerr << "ERROR: Memory allocation failed" << std::endl;
        return false;
    }
}

/**
 * Returns the input string without any white space.
 * @private
 * @return {string} string without whitespace
 */
std::string Board::TrimSpaceFromInputString_() {
    std::string str = this->input_string_;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t') {
            str.erase(i, 1);
            i--;
        }
    }
    return str;
}

/**
  * Calculates the sum of all manhattan distances of every piece on the board.
  * This is the heuristic function used for the A* algorithm.
  * @private
  * @return {int} The sum of the manhattan distances.
  */
int Board::CalculateSumOfManhattanDistances_() {
    if (this->goal_state_type_ == TOP_LEFT) {
        return this->CalculateSumOfManhattanDistancesTop_();
    } else if (this->goal_state_type_ == BOTTOM_RIGHT) {
        return this->CalculateSumOfManhattanDistancesBottom_();
    } else {
        std::cerr << "Invalid goal state type!" << std::endl;
        exit(1);
    }
}

/**
 * Calculates sum of the manhattan distances of every piece, using
 * the empty square at the top right as the goal state.
 * @return {int} The sum of the manhattan distances.
 * @private
 */
int Board::CalculateSumOfManhattanDistancesTop_() {
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
    return manhattanDistanceSum;
}

/**
 * Calculates sum of the manhattan distances of every piece, using
 * the empty square at the bottom left as the goal state.
 * @return {int} The sum of the manhattan distances.
 * @private
 */
int Board::CalculateSumOfManhattanDistancesBottom_() {
    int manhattanDistanceSum = 0;
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            int value = this->board_[x][y];
            if (value != 0) {
                int targetX = (value - 1) / 3;
                int targetY = (value - 1) % 3;
                int dx = x - targetX;
                int dy = y - targetY;
                manhattanDistanceSum += std::abs(dx) + std::abs(dy);
            }
        }
    }
    return manhattanDistanceSum;
}

/**
 * Determines what the goal state should be, empty position at 
 * top left or empty positin at bottom right, depending on 
 * whichever one yields the lowest manhattan distance.
 * @private
 */
void Board::DetermineGoalState_() {
    int bottom_goal_state_heuristic = 
        this->CalculateSumOfManhattanDistancesBottom_();
    int top_goal_state_heuristic = 
        this->CalculateSumOfManhattanDistancesTop_();
    if (bottom_goal_state_heuristic < top_goal_state_heuristic) {
        this->goal_state_type_ = BOTTOM_RIGHT;
    } else {
        this->goal_state_type_ = TOP_LEFT;
    }
}

/**
 * Recalculates the heuristic function, which estimates how many
 *   moves remain to get to goal state.
 *   Also sets estimated_moves_remaining_;
 * @private
 * @return {int} The calculated heuristic value.
 */
int Board::CalculateAndSetHeuristic_() {
    int value = this->CalculateSumOfManhattanDistances_();
    this->estimated_moves_remaining_ = value;
    return value;
}

/**
 * Swaps two values given their positions in the table. Used by move function.
 * @param point_1 one of the points to move
 * @param point_2 the second point to move
 */
void Board::Swap_(std::pair<int, int> point_1, std::pair<int, int> point_2) {
    assert(point_1.first < 3 && point_1.first >= 0);
    assert(point_1.second < 3 && point_1.second >= 0);
    assert(point_2.first < 3 && point_2.first >= 0);
    assert(point_2.second < 3 && point_2.second >= 0);

    int value_at_point_1 = this->GetValueAt(point_1.first, point_1.second);
    int value_at_point_2 = this->GetValueAt(point_2.first, point_2.second);
    this->board_[point_1.first][point_1.second] = value_at_point_2;
    this->board_[point_2.first][point_2.second] = value_at_point_1;
}

/**
 * Moves the empty space to the right.
 * @return {pair<boolean, Board>} first value indicates if move successful,
 *   second value is the newly created Board after the move.
 * @private
 */
void Board::Move_(int direction) {
    std::pair<int, int> current_position = this->GetEmptySpacePosition();
    std::pair<int, int> next_position;
    switch (direction) {
        case RIGHT:
            next_position = std::make_pair(current_position.first ,
                current_position.second + 1);
            break;
        case LEFT:
            next_position = std::make_pair(current_position.first ,
                current_position.second - 1);
            break;
        case UP:
            next_position = std::make_pair(current_position.first - 1 ,
                current_position.second);
            break;
        case DOWN:
            next_position = std::make_pair(current_position.first + 1 ,
                current_position.second);
            break;
    }
    this->Swap_(current_position, next_position);
    this->moves_made_ = this->moves_made_ + 1;
    this->empty_space_position_ = next_position;
    this->CalculateAndSetHeuristic_();
}

//////////////////////////
// Overloaded operators //
//////////////////////////

bool operator==(const Board& lhs, const Board& rhs) {
    // Do an element-by-element comparision of the boards.
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 3; ++y) {
            if (lhs.GetValueAt(x, y) != rhs.GetValueAt(x, y)) {
                return false;
            }
        }
    }
    return true;
}

bool operator<(const Board &lhs, const Board &rhs) {
    return lhs.GetRank() > rhs.GetRank();
}
