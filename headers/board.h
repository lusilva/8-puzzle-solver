/////////////////////////////////////////
// The header file for the board class //
/////////////////////////////////////////

#ifndef _board_h
#define _board_h

#include <string>
#include <utility>

/*
	The board class stores the states of the board and provides a way to interact with 
	the board by making moves.
    Below is a list of its private data members and their default value:
        - {string}         input_string_                  -> initialized to user input
        - {int}            moves_made_                    -> initialized to zero
        - {int}            estimated_moves_remaining_     -> initialized to -1
        - {int}            previous_state_                -> initialized to NULL
        - {int**}          board                          -> initialized to NULL
        - {pair<int, int>} empty_space_position_          -> initialized to (-1,-1) 
*/
class Board {
 public:
 	/*
 	 * Constructor for the Board class. 
 	 * @param {string} input The user input
 	 */
    explicit Board(const std::string &input) : input_string_(input),
      moves_made_(0), estimated_moves_remaining_(-1), previous_state_(NULL),
      board_(NULL), empty_space_position_(std::make_pair(-1, -1)) {}

    /**
     * Copy constructor for the board class.
     * @param {Board} the board to be copied
     */
    Board(const Board& board);

    /*
     * Destructor for the Board class. Deallocates dyanmically created memory.
     */
    ~Board() {this->DestroyBoard_();}

    /////////////////////////////////////
    // Getters for all private members //
    /////////////////////////////////////

    /**
     * Gets the number of moves made so far.
     * @return {int} the number of moves made.
     */
    const int GetMovesMade() const {return this->moves_made_;}

    /**
     * Gets the estimated number of moves remaining, sum of manhattan distances.
     * @return {int} the estimated number of moves remaining, used as heuristic.
     */
    const int GetEstimatedMovesRemaining() const {
        return this->estimated_moves_remaining_;}

    /**
     * Gets a pointer to the previous board state.
     * @return {Board*} the previous state.
     */
    const Board* GetPreviousState() const {return this->previous_state_;}

    /**
     * Gets the position of empty space as a pair of coordinates.
     * @return {pair<int, int>} (x,y) coordinates of the empty space.
     */
    const std::pair<int, int> GetEmptySpacePosition() const {
        return this->empty_space_position_;}

    /**
     * Gets the x coordinate of the empty space.
     * @return {int} the x coordinate of the empty space.
     */
    const int GetEmptySpaceRow() const {
        return this->empty_space_position_.first;}

    /**
     * Gets the y coordinate of the empty space.
     * @return {int} the y coordinate of the empty space.
     */
    const int GetEmptySpaceColumn() const {
        return this->empty_space_position_.second;}

    /**
     * Returns the value of the tile at board[x][y]
     * @param {int} x The x coordinate of the point. 
     * @param {int} y The y coordinate of the point.
     * @return {int} The value of the tile at those coordinates.
     */
    const int GetValueAt(int x, int y) const;

    /**
     * Returns the sum of the actual moves made plus 
     *   the estimated number of moves remaining.
     * @return {int} The rank of the board in the A* priority queue.
     */
    const int GetRank() const {
        return this->moves_made_ + this->estimated_moves_remaining_;}

    ////////////////////
    // End of getters //
    ////////////////////

    /**
     * Checks if a board has been allocated and initialized.
     * @return {boolean} true if board is valid.
     */
    bool IsValid() const;

    /*
     * Allocates memory and initializes the board. 
     * Must be called after making a new board instance, because this
     * actually initializes the private members to match the user input.
     * @return {boolean} true if allocation successful, false otherwise.
     */
    bool CreateBoard();

    /**
     * Prints the board.
     */
    void PrintBoard() const;

    /**
     * Gets the value of the heuristic function.
     * @return {int} The sum of the manhattan distances of all the tiles.
     */
    int GetHeuristicValue();

    ///////////////////////////////////////////////////////////////
    // Do actual moving of tiles on board.                       //
    // All these create new boards dynamically,                  //
    // it is the responsibility of the caller to delete them     //
    ///////////////////////////////////////////////////////////////


    /**
     * Determine whether a move to the right is possible.
     * @return {boolean} true if possible.
     */
    bool CanMoveRight();

    /**
     * Moves the empty space to the right.
     * @return {boolean} true if the move was successful, false otherwise.
     */
    bool MoveRight();

    /**
     * Determine whether a move to the left is possible.
     * @return {boolean} true if possible.
     */
    bool CanMoveLeft();

    /**
     * Moves the empty space to the left.
     * @return {boolean} true if the move was successful, false otherwise.
     */
    bool MoveLeft();

    /**
     * Determine whether a move down is possible.
     * @return {boolean} true if possible.
     */
    bool CanMoveDown();

    /**
     * Moves the empty space down.
     * @return {boolean} true if the move was successful, false otherwise.
     */
    bool MoveDown();

    /**
     * Determine whether a move up is possible.
     * @return {boolean} true if possible.
     */
    bool CanMoveUp();

    /**
     * Moves the empty space up.
     * @return {boolean} true if the move was successful, false otherwise.
     */
    bool MoveUp();

 private:
    /* The input string given by the user. */
    const std::string input_string_;
    /* Representation of a board as a dynamically allocated 2-D array */
    int** board_;
    /* (X,Y) position of the empty space on the board */
    std::pair<int, int> empty_space_position_;
    /* Actual number of moves made so far */
    int moves_made_;
    /* Estimated moves remaining, using heuristic function. */
    int estimated_moves_remaining_;
    /* A pointer to the previous board state. */
    Board* previous_state_;

    /* Free dynamically allocated memory for board. */
    void DestroyBoard_();

    /* Allocates dynamic memory used to store the board. */
    bool AllocateBoard_();

    /* Sets the x position of the blank space on the board */
    void SetEmptySpaceXCoordinate_(int x) {
        this->empty_space_position_.first = x;}

    /* Sets the y position of the blank space on the board */
    void SetEmptySpaceYCoordinate_(int y) {
        this->empty_space_position_.second = y;}

    /* Removes all spaces from input string */
    std::string TrimSpaceFromInputString_();

    /*
     * Calculates the sum of all manhattan distances of every piece on the board.
     * This is the heuristic function used for the A* algorithm.
     */
    int CalculateSumOfManhattanDistances_();

    /**
     * Recalculates the heuristic function, which estimates how many
     *   moves remain to get to goal state.
     *   Also sets estimated_moves_remaining_;
     * @private
     */
    int CalculateAndSetHeuristic_();

    /**
     * Swaps the values of two coordinates on the board with each other.
     * @param {pair<int, int>} The first point.
     * @param {pair<int, int>} The second point.
     * @private
     */
    void Swap_(std::pair<int, int> point_1, std::pair<int, int> point_2);

    /**
     * Actually moves the white space on the board.
     * @param {int} direction The direction of the move.
     */
    void Move_(int direction);
};

/**
 * Overloaded equality operator, takes in two board objects.
 * @param {Board} lhs The left hand side of the ==
 * @param {Board} rhs The right hand side of the ==
 * @return {boolean} true if board states are equal.
 */
bool operator==(const Board &lhs, const Board &rhs);

/**
 * Overloaded less than operator. 
 * @param {Board} lhs The left hand side of the <
 * @param {Board} rhs The right hand side of the <
 * @return {boolean} true if overall rank of the board on the left
 *   is less than the one on the right. (using GetRank())
 */
bool operator<(const Board &lhs, const Board &rhs);

#endif
