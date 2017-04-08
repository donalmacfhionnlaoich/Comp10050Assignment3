/*
 * playerOperations.c
 *
 *  Created on: 7 Apr 2017
 *      Author: Dónal
 */

#include "crossfireOperations.h"
#include "structs.h"

void MoveSlot (struct slot ** board,struct player_type player, const int numOfPlayers, int row, int column)
{
	int tempRow = player.row;
	int tempColumn = player.column;
	player.row = row;
	player.column = column;

	board[row][column].occupied = true;
	board[row][column].playersPresent[player.id]=1;	//Indicating user is present in slot by setting the corresponding index in the array to their id = 1;

	board[tempRow][tempColumn].playersPresent[player.id]=0;

	int i;
	//Checking if their are any players in the slot.
	for(i=0;i<numOfPlayers;i++)
	{
		//If a player is present, exit loop.
		if(board[tempRow][tempColumn].playersPresent[i]==1)
		{
			break;
		}
	}
	//After the for loop, if i = total number of players then no players are present in that slot. Set slot occupied to false.
	if(i==numOfPlayers)
	{
		board[tempRow][tempColumn].occupied = false;
	}
}
