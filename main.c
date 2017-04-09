/*
 * main.c

 *
 *  Created on: 29 Mar 2017
 *      Author: liliana
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include "crossfireOperations.h"
#include "structs.h"
#include "Prototypes.h"

int main(){

	setbuf(stdout,NULL);	//Fix error with eclipse on Windows.
	srand(time(NULL));

	int row, column;

	struct slot* currSlot = NULL;
	struct slot *foundSlots;
	bool explored[BOARD_SIZE][BOARD_SIZE];
	int count =0;

	//pointer to slot (0,0)
	struct slot *upLeft;

	//pointer to slot (0,boardSize -1)
	struct slot *upRight;

	//pointer to slot (boardSize - 1, 0)
	struct slot *downLeft;

	//pointer to slot (boardSize - 1, boardSize -1)
	struct slot *downRight;

	struct slot ** board = calloc(BOARD_SIZE, sizeof(struct slot *));


		for(int i =0; i< BOARD_SIZE; i++)
		{
			//This allocates in memory the space for the slots in each row of the board
			board[i] = calloc(BOARD_SIZE, sizeof(struct slot));
		}

	//Creates the board
	createBoard(board,BOARD_SIZE,&upLeft, &upRight, &downLeft, &downRight);

	unsigned int n, typeNum;
	printf("There can be 1-%d players in the game.\n", PLAYER_MAX);
	printf("How many players are there: ");
	scanf("%u", &n);		// Stores number of players in n
	/* Loop which ensures players number between 1 and defined player max (6) */
	while(n<2 || n>PLAYER_MAX)
	{
		puts("That number of players is invalid. Please enter a valid number of players.");
		scanf("%u", &n);	// Re-loops if incorrect number is entered
	}

	struct player_type *player;
	player = calloc(n,sizeof(struct player_type));
	puts("\nA player's name can have a maximum length of 19 characters.");
	puts("There are 4 types of player: Elf, Human, Ogre and Wizard.");	//Giving information to user on the possible types of player_type and name specs.
	for(unsigned i=0; i<n; i++)
	{
		printf("\nEnter Player %d's name: ", i+1);
		scanf("%19s", player[i].name);	//Ensuring the maximum of characters of name is at most 19 so that there is one space for the null terminator.
		printf("\n----------Enter Player %d's type---------\n", i+1);
		printf("1 - Human, 2 - Ogre, 3 - Wizard, 4 - Elf:\n");
		scanf("%u", &typeNum);		// User input for player type
		while(typeNum < 1 || typeNum > 4)
		{	// Loops while entered digit is not 1-4
			puts("Sorry but you must enter a number between 1 & 4:\n");
			scanf("%u", &typeNum);
		}
		player[i].lifepoints = 100.0;		// Sets everybody's LP's too 100.0 as stated
											// Must be floating point for attack calculations
		player[i].id = i;
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
	}
	printPlayersStatus(player, n);
	int playersOut = 0;

	do{

	}while(n-1>playersOut);

	if(n>playersOut)
	{
		for(int i=0;i<n;i++)
		{
			if(player[i].lifepoints>0)
			{
				printf("%s has won the game! GG",player[i].);
			}
		}
	}
#if 0
	/*	Asks the user the row and the column of the slot
		s/he wants to retrieve from the board.
		Note that the user needs to know the size of the board to input
		the correct row and column of the slot s/he wants to retrieve */
	getDesiredElement(BOARD_SIZE, &row,&column);

	//Finds the slot


	/*If the the required slot is closer to the down-right
	 * corner of the board the search starts from downRight,
	 * which points to slot at position (boardSize-1, boarSize -1)*/
	if(row >= BOARD_SIZE/2){
		if(column >= BOARD_SIZE/2)
			currSlot = reachDesiredElement(row,column,downRight);
		else
		/*If the the required slot is closer to the down-left
		* corner of the board the search starts from downLeft,
		* which points to slot at position (boardSize-1, 0)*/
			currSlot = reachDesiredElement(row,column,downLeft);
	} else {
		/*If the the required slot is closer to the up-right
		* corner of the board the search starts from upRight,
		* which points to slot at position (0, boarSize -1)*/
		if(column >= BOARD_SIZE/2)
			currSlot = reachDesiredElement(row,column, upRight);
		/*If the the required slot is closer to the up-left
		* corner of the board the search starts from upLeft,
		* which points to slot at position (0, 0)*/
		else currSlot = reachDesiredElement(row,column,upLeft);
	}

	for(int i=0; i<BOARD_SIZE; i++){
		for(int j=0; j<BOARD_SIZE;j++){
			explored[i][j] = false;
		}
	}

	foundSlots = malloc(BOARD_SIZE * BOARD_SIZE * sizeof(struct slot ));
	printf("\n\nFunction findSlotsinvoked:\n");

	if(currSlot!= NULL){
		//invokes function findSlots. The required distance is a constant
		//However you can reuse this function providing as input any arbitrary distance
		findSlots(REQ_DISTANCE, 0, currSlot, foundSlots, &count, explored);
		for(int i=0; i<count; i++){
			printf("(%d, %d)-> ",foundSlots[i].row, foundSlots[i].column);
		}
	}
#endif
	return 0;
}
