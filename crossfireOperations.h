/*
 * crossfireOperations.h
 *
 *  Created on: 29 Mar 2017
 *      Author: liliana
 */

#ifndef CROSSFIREOPERATIONS_H_
#define CROSSFIREOPERATIONS_H_



#endif /* CROSSFIREOPERATIONS_H_ */

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
	//row number
	int row;
	//column number
	int column;

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

/*
 * Functions getBoardSize and getDesiredElement
 * manage the interaction with the users
 */

//Asks the user to provide as input the size of the board
//Returns the size of the board
int getBoardSize();

//Asks the user to insert the row and the column of the element
//she wants to find given a board of size equal to maxsize
void getDesiredElement(int maxsize, int * row, int * col);

/*
 * Functions createBoard and reachDesiredElement
 * manage the creation and manipulation of the board
 */
/*
 * This function creates the board
 * Parameters:
 * 	boardSize: the size of the board
 * 	upLeft: pointer of pointer to slot at position (0, 0)
 * 	upRight: pointer of pointer to slot at position (0, size -1)
 * 	downLeft: pointer of pointer to slot at position (size -1, 0)
 * 	upLeft: pointer of pointer to slot at position (size - 1, size -1)
 */
void createBoard(int boardSize, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight);

/*
 * This function traverses the board to find a slot at a predefined
 * position (row, column)
 * Parameters:
 * 	row: the row in which the desired slot is located
 * 	column: the column in which the desired slot is located
 * 	initialSlot: the slot from which the slot search should start
 */
void reachDesiredElement(int row, int column, struct slot * initialSlot);
