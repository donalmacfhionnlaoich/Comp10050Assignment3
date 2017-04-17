/*
 * boardCreation.c

 *
 *  Created on: 29 Mar 2017
 *      Author: liliana
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crossfireOperations.h"



/*
 * This function creates the board
 * Parameters:
 * 	size: the size of the board
 * 	upLeft: pointer of pointer to slot at position (0, 0)
 * 	upRight: pointer of pointer to slot at position (0, boardSize -1)
 * 	downLeft: pointer of pointer to slot at position (boardSsize -1, 0)
 * 	upLeft: pointer of pointer to slot at position (boardSize - 1, boardSize -1)
 */
void createBoard(struct slot **board, int boardSize)
{
	//The board is represented as a pointer of pointer to slots
	//Occupied int and playersPresent array all set to 0 by default because of previous calloc
	for(int i =0; i< boardSize; i++){
		//For each slot it sets up the row and column number
		for(int j=0;j < boardSize; j++)
		{
			board[i][j].row = i;
			board[i][j].column = j;
			//Assigning random slot type
			int x = rand() % 3;
			board[i][j].slot_type = x;
			//Copying name of slot to struct member slot_name
			if(x == 0){
			strcpy(board[i][j].slot_name,"Level Ground");
				}
			else if(x == 1){
			strcpy(board[i][j].slot_name, "City");
			}
			else if(x == 2){
			strcpy(board[i][j].slot_name, "Hill");
			}
	}

	//It sets up the adjacent slots for the slots that are
	//not at the borders. These slots have 4 adjacent elements
	for(int i = 1; i< boardSize-1; i++){
		for(int j=1;j < boardSize-1; j++){
			board[i][j].up = &board[i-1][j];
			board[i][j].right = &board[i][j+1];
			board[i][j].down = &board[i+1][j];
			board[i][j].left = &board[i][j-1];
		}
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last row, except the slots at the edges.
	//
	for(int j = 1; j < boardSize -1; j++){
		//It sets up the adjacent slots for the slots that are in the first row.
		//These slots don't have an adjacent element on top of them
		// because they are on the first row of the board
		board[0][j].right = &board[0][j+1];
		board[0][j].left = &board[0][j-1];
		board[0][j].down = &board[1][j];
		board[0][j].up = NULL;

		//It sets up the adjacent slots for the slots that are in the last row.
		//These slots don't have an adjacent element on down them
		// because they are on the last row of the board
		board[boardSize - 1][j].right = &board[boardSize - 1][j+1];
		board[boardSize -1][j].left = &board[boardSize - 1][j-1];
		board[boardSize - 1][j].up = &board[boardSize - 2][j];
		board[boardSize - 1][j].down = NULL;
	}

	//It sets up the adjacent slots for the slots that are
	//in the first and the last column, except the slots at the edges.
	//
	for(int i = 1; i < boardSize -1; i++){
		//It sets up the adjacent slots for the slots that are in the first column.
		//These slots don't have an adjacent element on the left
		// because they are on the first column of the board
		board[i][0].right = &board[i][1];
		board[i][0].up = &board[i-1][0];
		board[i][0].down = &board[i+1][0];
		board[i][0].left = NULL;

		//It sets up the adjacent slots for the slots that are in the last column.
		//These slots don't have an adjacent element on the right
		// because they are on the last column of the board
		board[i][boardSize-1].left = &board[i][boardSize-2];
		board[i][boardSize -1].up = &board[i -1][boardSize-1];
		board[i][boardSize -1].down = &board[i+1][boardSize -1];
		board[i][boardSize -1].right = NULL;
	}


		//It sets up the adjacent slots for the slot at position (0,0).
		//This only has only 2 adjacent slots: right and down
		board[0][0].right = &board[0][1];
		board[0][0].down = &board[1][0];

		//It sets up the adjacent slots for the slot at position (0,boardSize -1).
		//This only has only 2 adjacent slots: left and down
		board[0][boardSize-1].left = &board[0][boardSize-2];
		board[0][boardSize -1].down = &board[1][boardSize -1];

		//It sets up the adjacent slots for the slot at position (boarSize -1 ,0).
		//This only has only 2 adjacent slots: up and right
		board[boardSize -1][0].right = &board[boardSize -1][1];
		board[boardSize -1][0].up = &board[boardSize -2][0];

		//It sets up the adjacent slots for the slot at position (boarSize -1 ,boardSize-1).
		//This only has only 2 adjacent slots: up and left
		board[boardSize - 1][boardSize-1].up = &board[boardSize-2][boardSize-1];
		board[boardSize - 1][boardSize -1].left = &board[boardSize -1][boardSize -2];
	}
}

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
void findSlots(int reqDist, int currDist,  struct slot * currSlot, int * playersFound, int *checker, int x)
{
	//The base case: the current slot is at the required distance from the starting slot
	if(currDist == reqDist){
		//the current slot was not explored
		if(currSlot->explored == false)
		{
			//The current slot is occupied
			if(currSlot->occupied == true){
				// Search through array playersPresent for true indicating player i is occupying current slot
				for(int i =0; i<PLAYER_MAX;i++){
					if(currSlot->playersPresent[i]==1 && i!=x && playersFound[i] != 1){
						playersFound[i] = 1;	// Set playerFound to true so for player i
						(*checker) ++;		//increment checkerD
					}
				}
			}
		}
	}
	//The recursive call: the current slot is at a distance that is less than the required distance (more slots still have to be traversed)
	else{
		//if the current slot has the up slot != NULL (i.e. the slot is not in the first row)
		if(currSlot->up != NULL){
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the up slot
			findSlots(reqDist, currDist +1,  currSlot->up, playersFound, checker, x);
		}
		//if the current slot has the right slot != NULL (i.e. the slot is not in the last column)
		if(currSlot->right != NULL){
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the right slot
			findSlots(reqDist, currDist +1,  currSlot->right, playersFound, checker, x);
		}
		//if the current slot has the down slot != NULL (i.e. the slot is not in the last row)
		if(currSlot->down != NULL){
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the down slot
			findSlots(reqDist, currDist +1,  currSlot->down, playersFound, checker, x);
		}
		//if the current slot has the left slot != NULL (i.e. the slot is not in the first column)
		if(currSlot->left != NULL){
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the left slot
			findSlots(reqDist, currDist +1,  currSlot->left, playersFound, checker, x);
		}
	}
}

int checkNearAttack(struct slot ** board, int row, int column, int x, int * playersFound)
{	// Set to false so will return false if no adjacent players found
	bool check = false;	
	/* Check for another player in same slot */
	if((checkSlot(row,column,board, x, playersFound))==true) //Check for occupant (see function body below)
	{
		check = true;
	}
	/* Check for slot above if player not on top row */
	if(row+1<BOARD_SIZE)
	{
		if((checkSlot(row+1,column,board, x, playersFound))==true) //Check for occupant (see function body below)
		{
			check = true;
		}
	}
	/* Check for slot to the right if player not on last column */
	if(column+1<BOARD_SIZE)
	{
		if((checkSlot(row,column+1,board, x, playersFound))==true) //Check for occupant (see function body below)
		{
			check = true;
		}
	}
	/* Check for slot below if player not on bottom row */
	if(row-1>=0)
	{
		if((checkSlot(row-1,column,board, x, playersFound))==true) //Check for occupant (see function body below)
		{
			check = true;
		}
	}
	/* Check for slot to the left if player not on first column */
	if(column-1>=0)
	{
		if((checkSlot(row,column-1,board, x, playersFound))==true) //Check for occupant (see function body below)
		{
			check = true;
		}
	}
	return check;	// return false if no condition met, otherwise true
}

int checkSlot(int row, int column, struct slot ** board, int x, int * playersFound)
{	// If board is occupied & player present is not current player 
	if(board[row][column].occupied)
	for(int i=0;i<PLAYER_MAX;i++)
	{
		if(board[row][column].playersPresent[i] ==1 && i!=x)
		{
			playersFound[i]=1;	// set playerFound[i] so player can be chosen
			return true;		// return true 
		}
	 }
	return false;	// otherwise false
}
