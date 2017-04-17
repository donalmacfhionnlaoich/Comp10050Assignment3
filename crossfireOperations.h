/*
 * crossfireOperations.h
 *
 *  Created on: 29 Mar 2017
 *      Author: liliana
 */

#ifndef CROSSFIREOPERATIONS_H_
#define CROSSFIREOPERATIONS_H_



#endif /* CROSSFIREOPERATIONS_H_ */

#define BOARD_SIZE 7
#define REQ_DISTANCE 3
#define PLAYER_MAX 6

enum playerType {humanType, ogreType, wizardType, elfType};
enum slotType {level_ground, cityType, hillType};
/*
 * Definition of boolean types
 * This avoids using <stdbool.h>
 */
typedef int bool;
enum { false, true };

/*
 * The slot template
 */
struct slot{
	bool explored;
	//row number
	int row;
	//column number
	int column;
	//Type of slot
	char slot_name[15];
	int slot_type;
	//Represents if there is at least one player in the slot
	int occupied;
	//Represents which players are in the slot
	int playersPresent[PLAYER_MAX];
	// adjacent left slot
	struct slot *left;
	// adjacent right slot
	struct slot *right;
	// adjacent up slot
	struct slot *up;
	// adjacent down slot
	struct slot *down;
}slot;

/*
 * FUNCTIONS PROTOTYPES
 */



/*Function createBoard manages the creation of the board */
/*
 * This function creates the board
 * Parameters:
 * 	boardSize: the size of the board
 * 	upLeft: pointer of pointer to slot at position (0, 0)
 * 	upRight: pointer of pointer to slot at position (0, size -1)
 * 	downLeft: pointer of pointer to slot at position (size -1, 0)
 * 	upLeft: pointer of pointer to slot at position (size - 1, size -1)
 */
void createBoard(struct slot **board, int boardSize);


/*
 * The recursive function that traverses the board to find the slots at a predefined
 * distance from the current slot and place them in foundSlots.
 * Parameters:
 * 	reqDist: the required distance from the starting slot
 * 	currDist: the distance of the current slot from the starting slot
 * 	currSlot: a pointer to the current slot that is traversed
 * 	foundSlots: the array of slots that are at a required distance from the starting slot
 * 	count: pointer to an integer representing the number of slots that are found to be at a required distance from the starting slot
 * 	explored: matrix indicating for each slot at row x and column y has been traversed (true) or not (false)
 */
void findSlots(int reqDist, int currDist,  struct slot * currSlot, int * playersFound, int *checker, int x);

/* Function which takes a single slot & player checks if it is occupied by
	someone other than the player and if so returns true
*	x: index of player
* 	playerFound[]: array used to store ID of found players by setting that element to 1 i.e. [ID Of Found Player] = 1
* 	board: pointer to board structs
* 	row: row number in board[row][column] to be checked for occupant
*	column: column number in board[row][column] to be checked for occupant
*/
int checkSlot(int row, int column, struct slot ** board, int x, int * playersFound);

/* This function calls the function checkSlot for each adjacent slot (provided they exist)
and returns true if any are occupied by another player */
int checkNearAttack(struct slot ** board, int row, int column, int x, int * playersFound);
