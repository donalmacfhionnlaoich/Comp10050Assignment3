/*
 * playerOperations.c
 *
 *  Created on: 7 Apr 2017
 *      Author: Dónal
 */

#include "crossfireOperations.h"
#include "structs.h"
#include "Prototypes.h"
#include <stdio.h>

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

	if(board[player.row][player.column].slot_type == cityType)
	{
		city(player);
	}
	else if(board[player.row][player.column].slot_type == hillType)
	{
		hill(player);
	}
}

void playerQuit(struct slot ** board,struct player_type player)
{
	board[player.row][player.column].playersPresent[player.id]=0;	//Removing player from current slot

	int i;
	//Checking if their are any players in the slot.
	for(i=0;i<PLAYER_MAX;i++)
	{
		//If a player is present, exit loop.
		if(board[player.row][player.column].playersPresent[i]==1)
		{
			break;
		}
	}
	//After the for loop, if i = total number of players then no players are present in that slot. Set slot occupied to false.
	if(i==PLAYER_MAX)
	{
		board[player.row][player.column].occupied = false;
	}

	player.lifepoints = 0;
	player.row = -1;
	player.column = -1;
}

/*void playerMoveChoice(struct slot ** board, struct player_type **player, char *slotChoice, int n, int i)
{
	printf("What slot would you like to move to:\n");
								if((board[player.row][player.column].up)!=NULL){
									printf("u - for slot above\n");
								}
								if((board[player.row][player.column].down)!=NULL){
									printf("d - for slot below\n");
								}
								if((board[player.row][player.column].left)!=NULL){
								printf("l - for slot to the left\n");
								}
								if((board[player.row][player.column].right)!=NULL){
									printf("r - for slot to the right\n?");
								}
								//fflush(stdin);
								//scanf("%c", &slotChoice);
								do{
									printf("Choice: ");
									fflush(stdin);
									scanf(" %c", &(*slotChoice));
									switch(*slotChoice)
									{
										case 'u':
											if((board[player.row][player.column].up)!=NULL){
												MoveSlot(board, player, n, player.row+1, player.column);
												break;
											}
											else{
												printf("Incorrect value entered! case u\n");
												*slotChoice = -1;
												break;
											}
										case 'd':
											if((board[player[i].row][player[i].column].down)!=NULL){
												MoveSlot(board, player[i], n, player[i].row-1, player[i].column);
												break;
											}
											else{
												printf("Incorrect value entered! case d\n");
												*slotChoice = -1;
												break;
											}
										case 'l':
											if((board[player[i].row][player[i].column].left)!=NULL){
												MoveSlot(board, player[i], n, player[i].row, player[i].column-1);
												break;
											}
											else{
												printf("Incorrect value entered! case l\n");
												*slotChoice = -1;
												break;
											}
										case 'r':
											if((board[player[i].row][player[i].column].right)!=NULL){
												MoveSlot(board, player[i], n, player[i].row, player[i].column+1);
												break;
											}
											else{
												printf("Incorrect value entered! case r\n");
												*slotChoice = -1;
												break;
											}
										default:
											printf("Incorrect value entered! default\n");
											*slotChoice = -1;
											break;
									}
								}while(slotChoice==-1); //why??
}*/


