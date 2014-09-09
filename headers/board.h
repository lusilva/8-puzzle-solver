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
      board_(NULL), empty_space_position_(std::make_pair(-1,-1)) {}

    /*
     * Destructor for the Board class. Deallocates dyanmically created memory.
     */
    ~Board() {this->DestroyBoard_();}

    /////////////////////////////////////
    // Getters for all private members //
    /////////////////////////////////////

    /**
     * Gets the input string used to create the table.
     * @return {string} the input string
     */
    const std::string GetInputString() const {return this->input_string_;}

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
     * @return {pair} (x,y) coordinates of the empty space.
     */
    const std::pair<int, int> GetEmptySpacePosition() const {
        return this->empty_space_position_;}

    /**
     * Returns the value of the tile at board[x][y]
     * @param {int} x The x coordinate of the point. 
     * @param {int} y The y coordinate of the point.
     * @return {int} The value of the tile at those coordinates.
     */
    const int GetValueAt(int x, int y);

    ////////////////////
    // End of getters //
    ////////////////////
    
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
    void PrintBoard();

    /**
     * Gets the value of the heuristic function.
     * @return {int} The sum of the manhattan distances of all the tiles.
     */
    int GetHeuristicValue();



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
     */
    int CalculateAndSetHeuristic_();

    /**
     * Move the empty space to the right.
     * Returns true if move successful, false otherwise.
     */
    bool MoveRight_();

    /**
     * Move the empty space to the left.
     * Returns true if move successful, false otherwise.
     */
    bool MoveLeft_();

    /**
     * Move the empty space up.
     * Returns true if move successful, false otherwise.
     */
    bool MoveUp_();

    /**
     * Move the empty space down.
     * Returns true if move successful, false otherwise.
     */
    bool MoveDown_();
};



#endif
