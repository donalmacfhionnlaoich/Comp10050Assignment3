/*
 * playerOperations.c
 *
 *  Created on: 7 Apr 2017
 *      Author: D�nal
 */

#include "crossfireOperations.h"
#include "structs.h"
#include "Prototypes.h"
#include <stdio.h>
#include <string.h>

void MoveSlot (struct slot ** board,struct player_type * player, const int numOfPlayers, int row, int column, int i)
{
	//Storing players previous position
	int tempRow = player[i].row;
	int tempColumn = player[i].column;

	//Assigning new position to player
	player[i].row = row;
	player[i].column = column;

	//Indicating in moved to slot that it is occupied. Adding player to presentPlayers
	board[row][column].occupied = true;
	board[row][column].playersPresent[player[i].id]=1;	//Indicating user is present in slot by setting the corresponding index in the array to their id = 1;

	//Removing player from previous slot playersPresent
	board[tempRow][tempColumn].playersPresent[player[i].id]=0;

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
	//After the for loop, if k = total number of players then no players are present in that slot. Set slot occupied to false.
	if(k==numOfPlayers)
	{
		board[tempRow][tempColumn].occupied = false;
	}

	//Applying modifications of slot moved to to player
	if(board[player[i].row][player[i].column].slot_type == cityType)
	{
		city(&player[i]);
	}
	else if(board[player[i].row][player[i].column].slot_type == hillType)
	{
		hill(&player[i]);
	}
}

void playerQuit(struct slot ** board,struct player_type * player)
{
	board[player->row][player->column].playersPresent[player->id]=0;	//Removing player from current slot
	//Int to hold number of players who've left/died
	extern int playersOut;
	int i;
	//Checking if their are any players in the slot.
	for(i=0;i<PLAYER_MAX;i++)
	{
		//If a player is present, exit loop.
		if(board[player->row][player->column].playersPresent[i]==1)
		{
			break;
		}
	}
	//After the for loop, if i = total number of players then no players are present in that slot. Set slot occupied to false.
	if(i==PLAYER_MAX)
	{
		board[player->row][player->column].occupied = false;
	}

	//Setting player off the board and dead
	player->lifepoints = 0;
	player->row = -1;
	player->column = -1;
	playersOut++;	//Incrementing number of players dead/quit
}

void playerCheck(struct slot ** board, struct player_type * player, int * checkerD, int x, int * playersFound)
{
	//Resetting checks of possible attacks to false
	player[x].nearCheck = false;
	player[x].distantCheck = false;
	player[x].magicCheck = false;

	//Resetting checkerD to false
	*checkerD = 0;

	for(int k=0;k<BOARD_SIZE;k++)
	{
		for(int l=0;l<BOARD_SIZE;l++)
		{
			board[k][l].explored = false;
		}
	}

	//Resetting playersFOund array to 0
	for(int i=0;i<PLAYER_MAX;i++)
	{
		playersFound[i]=0;
	}

	//Checking if a near attack is possible and assigning result to player's check.
	player[x].nearCheck = checkNearAttack(board, player[x].row, player[x].column, x, playersFound);

	//checking if a distant attack is possible
	for(int i=2;i<5;i++)
	{
		findSlots(i, 0,  &board[player[x].row][player[x].column], playersFound, checkerD, x);
	}
	//Setting distant check to true if there is another player found
	if((*checkerD)>0)	//1 because the player always finds them-self
	{
		player[x].distantCheck = true;
	}

	//Checking if player can make a magic attack
	if((player[x].smartness + player[x].magicskills)>150)
	{
		player[x].magicCheck = true;
	}
}

void playerMoveChoice(struct slot ** board, struct player_type * player, char *slotChoice, int n, int i)
{
	//Printing which slots the player can move to.
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

	do{
		//Prompting user for which slot they would like to  move to
		printf("Choice: ");
		fflush(stdin);
		scanf(" %c", &(*slotChoice));

		switch(*slotChoice)
		{
			case 'd':	//Player wants to move down
				//Checking if the chosen slot exists
				if((board[player[i].row][player[i].column].down)!=NULL){
					//Moving player
					MoveSlot(board, player, n, player[i].row+1, player[i].column, i);
					printf("\n\n%s (Player %d) has moved to slot (%d,%d)\n\n",player[i].name, i+1, player[i].row, player[i].column);
					break;
				}
				else{	//If slot chosen does not exist, alert user and set slotChoice so that they get prompted to choose a different slot
					printf("Incorrect value entered!\n");
					*slotChoice = -1;
					break;
				}
			case 'u':	//Player wants to move up
				//Checking if the chosen slot exists
				if((board[player[i].row][player[i].column].up)!=NULL){
					//Moving player
					MoveSlot(board, player, n, player[i].row-1, player[i].column, i);
					printf("\n\n%s (Player %d) has moved to slot (%d,%d)\n\n",player[i].name, i+1, player[i].row, player[i].column);
					break;
				}
				else{	//If slot chosen does not exist, alert user and set slotChoice so that they get prompted to choose a different slot
					printf("Incorrect value entered!\n");
					*slotChoice = -1;
					break;
				}
			case 'l':	//Player wants to move left
				//Checking if the chosen slot exists
				if((board[player[i].row][player[i].column].left)!=NULL){
					//Moving player
					MoveSlot(board, player, n, player[i].row, player[i].column-1, i);
					printf("\n\n%s (Player %d) has moved to slot (%d,%d)\n\n",player[i].name, i+1, player[i].row, player[i].column);
					break;
				}
				else{	//If slot chosen does not exist, alert user and set slotChoice so that they get prompted to choose a different slot
					printf("Incorrect value entered!\n");
					*slotChoice = -1;
					break;
				}
			case 'r':	//Player wants to move right
				//Checking if the chosen slot exists
				if((board[player[i].row][player[i].column].right)!=NULL){
					//Moving player
					MoveSlot(board, player, n, player[i].row, player[i].column+1, i);
					printf("\n\n%s (Player %d) has moved to slot (%d,%d)\n\n",player[i].name, i+1, player[i].row, player[i].column);
					break;
				}
				else{	//If slot chosen does not exist, alert user and set slotChoice so that they get prompted to choose a different slot
					printf("Incorrect value entered!\n");
					*slotChoice = -1;
					break;
				}
			default:	//Invalid value was entered. Alert user and set slotChoice so that they get prompted to choose a different slot
				printf("Incorrect value entered!\n");
				*slotChoice = -1;
				break;
		}
	}while(*slotChoice == -1);	//Continues until a valid slot is chosen to move to
}

//Function to initialize player
void playerInitialization(struct slot ** board, struct player_type * player,int i)
{
	unsigned int typeNum;	//Variable to hold player type
	//Prompting and receiving user's name
	printf("\nEnter Player %d's name: ", i+1);
	scanf("%19s", player[i].name);	//Ensuring the maximum of characters of name is at most 19 so that there is one space for the null terminator.
	//Prompting and recieving player's type
	printf("\n----------Enter Player %d's type---------\n", i+1);
	printf("1 - Human, 2 - Ogre, 3 - Wizard, 4 - Elf:\n");
	scanf("%u", &typeNum);		// User input for player type

	while(typeNum < 1 || typeNum > 4)
	{	// Loops while entered digit is not a valid type
		puts("Sorry but you must enter a number between 1 & 4:\n");
		scanf("%u", &typeNum);
	}
	player[i].lifepoints = 100.0;		// Sets everybody's LP's too 100.0 as stated
										// Must be floating point for attack calculations
	player[i].id = i;	//Setting player's ID
	/* Switch that copies player's type and respective capabilities to each struct member */
	switch(typeNum - 1)
	{
		case humanType:
			strcpy(player[i].type, "Human");
			human(&player[i], board);		// Elf function (see playerTypes.c)
			break;
		case ogreType:
			strcpy(player[i].type, "Ogre");
			ogre(&player[i], board);		// Human function (see playerTypes.c)
			break;
		case wizardType:
			strcpy(player[i].type, "Wizard");
			wizard(&player[i], board);		// Ogre function (see playerTypes.c)
			break;
		case elfType:
			strcpy(player[i].type, "Elf");
			elf(&player[i], board);		// Wizard function (see playerTypes.c)
			break;
	}

	//If the slot the player is in is either a hill or city slot, modify their abilities accordingly
	if(board[player[i].row][player[i].column].slot_type == cityType)
	{
		city(&player[i]);
	}
	else if(board[player[i].row][player[i].column].slot_type == hillType)
	{
		hill(&player[i]);
	}
}
