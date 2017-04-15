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

void MoveSlot (struct slot ** board,struct player_type * player, const int numOfPlayers, int row, int column, int i)
{
	printf("Original: (%d,%d)\n",player[i].row,player[i].column);
	int tempRow = player[i].row;
	int tempColumn = player[i].column;
	player[i].row = row;
	player[i].column = column;
	printf("Changed: (%d,%d)\n",player[i].row,player[i].column);
	puts("Basics done");
	board[row][column].occupied = true;
	board[row][column].playersPresent[player[i].id]=1;	//Indicating user is present in slot by setting the corresponding index in the array to their id = 1;

	board[tempRow][tempColumn].playersPresent[player[i].id]=0;
	puts("Prsence removed");
	int k;
	//Checking if their are any players in the slot.
	for(k=0;k<numOfPlayers;k++)
	{
		//If a player is present, exit loop.
		if(board[tempRow][tempColumn].playersPresent[k]==1)
		{
			break;
		}
	}
	puts("previous slot checked");
	//After the for loop, if k = total number of players then no players are present in that slot. Set slot occupied to false.
	if(k==numOfPlayers)
	{
		board[tempRow][tempColumn].occupied = false;
	}

	if(board[player[i].row][player[i].column].slot_type == cityType)
	{
		puts("calling city");
		city(player[i]);
	}
	else if(board[player[i].row][player[i].column].slot_type == hillType)
	{
		puts("Calling hill");
		hill(player[i]);
	}
	puts("done");
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

void playerCheck(struct slot ** board, struct player_type * player, int * checkerD, int x, int * playersFound)
{
	//Resetting checks of possible atatcks to false
	player[x].nearCheck = false;
	player[x].distantCheck = false;
	player[x].magicCheck = false;

	puts("Set checks to false");
	//Resetting checkerD to false
	*checkerD = 0;
	//int explored[BOARD_SIZE][BOARD_SIZE] = {false};

	for(int k=0;k<BOARD_SIZE;k++)
	{
		for(int l=0;l<BOARD_SIZE;l++)
		{
			board[k][l].explored = false;
		}
	}


	//memset was causing errors
	//memset(&explored, 0, sizeof(bool) * BOARD_SIZE*BOARD_SIZE);

	//Resetting playersFOund array to 0
	for(int i=0;i<PLAYER_MAX;i++)
	{
		playersFound[i]=0;
	}

	//Checking if a near attack is possible and assigning result to player's check.
	player[x].nearCheck = checkNearAttack(board, player[x].row, player[x].column, x, playersFound);

	puts("nearcheck done");
	//checking if a distant attack is possible
	for(int i=2;i<5;i++)
	{
		findSlots(i, 0,  &board[player[x].row][player[x].column], playersFound, checkerD, x);
	}
	printf("Find slots %d completed.\n",x);
	//Setting distant check to true if there is another player found
	if(checkerD>0)	//1 because the player always finds them-self
	{
		player[x].distantCheck = true;
	}
	puts("Distant check ran");

	//Checking if player can make a magic attack
	if((player[x].smartness + player[x].magicskills)>150)
	{
		player[x].magicCheck = true;
	}
	puts("magic check ran");
}

void playerMoveChoice(struct slot ** board, struct player_type * player, char *slotChoice, int n, int i)
{
	//playerMoveChoice( board, player, &slotChoice, n, i);
	printf("What slot would you like to move to:\n");
	if((board[player[i].row][player[i].column].up)!=NULL){
		printf("u - for slot above\n");
	}
	if((board[player[i].row][player[i].column].down)!=NULL){
		printf("d - for slot below\n");
	}
	if((board[player[i].row][player[i].column].left)!=NULL){
	printf("l - for slot to the left\n");
	}
	if((board[player[i].row][player[i].column].right)!=NULL){
		printf("r - for slot to the right\n?");
	}
	//fflush(stdin);
	//scanf("%c", &slotChoice);
	do{
		printf("Choice: ");
		fflush(stdin);
		scanf(" %c", &(*slotChoice));
		printf("Char entered is %c\n",*slotChoice);
		switch(*slotChoice)
		{
			case 'd':
				if((board[player[i].row][player[i].column].up)!=NULL){
					puts("Calling move slot");
					printf("Original: (%d,%d)\n",player[i].row,player[i].column);
					MoveSlot(board, player, n, player[i].row+1, player[i].column, i);
					printf("After: (%d,%d)\n",player[i].row,player[i].column);
					puts("Move slot called");
					break;
				}
				else{
					printf("Incorrect value entered! case u\n");
					*slotChoice = -1;
					break;
				}
			case 'u':
				if((board[player[i].row][player[i].column].down)!=NULL){
					puts("Calling move slot");
					printf("Original: (%d,%d)\n",player[i].row,player[i].column);
					MoveSlot(board, player, n, player[i].row-1, player[i].column, i);
					printf("After: (%d,%d)\n",player[i].row,player[i].column);
					puts("Move slot called");
					break;
				}
				else{
					printf("Incorrect value entered! case d\n");
					*slotChoice = -1;
					break;
				}
			case 'l':
				if((board[player[i].row][player[i].column].left)!=NULL){
					puts("Calling move slot");
					printf("Original: (%d,%d)\n",player[i].row,player[i].column);
					MoveSlot(board, player, n, player[i].row, player[i].column-1, i);
					printf("After: (%d,%d)\n",player[i].row,player[i].column);
					puts("Move slot called");
					break;
				}
				else{
					printf("Incorrect value entered! case l\n");
					*slotChoice = -1;
					break;
				}
			case 'r':
				if((board[player[i].row][player[i].column].right)!=NULL){
					puts("Calling move slot");
					MoveSlot(board, player, n, player[i].row, player[i].column+1, i);
					puts("Move slot called");
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
	}while(*slotChoice == -1);
}

