/*
 * main.c

 *
 *  Created on: 29 Mar 2017
 *      Author: liliana
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "crossfireOperations.h"
#include "structs.h"
#include "Prototypes.h"

int playersOut;

int main(){

	setbuf(stdout,NULL);	//Fix error with eclipse on Windows.
	srand(time(NULL));		// Seed time to rand() function for use in slot and player assign

	//pointer to slot (0,0)
	struct slot *upLeft;

	//pointer to slot (0,boardSize -1)
	struct slot *upRight;

	//pointer to slot (boardSize - 1, 0)
	struct slot *downLeft;

	//pointer to slot (boardSize - 1, boardSize -1)
	struct slot *downRight;
	// Dynamically allocate memory for slots and initialize to ZERO/NULL
	struct slot ** board = calloc(BOARD_SIZE, sizeof(struct slot *));

	//This allocates in memory the space for each row per column of the board (i.e.BOARD_SIZE * BOARD_SIZE)
	for(int i =0; i< BOARD_SIZE; i++)
	{
		//This allocates in memory the space for the slots in a row of the board
		board[i] = calloc(BOARD_SIZE, sizeof(struct slot));
	}

	//Creates the board
	createBoard(board,BOARD_SIZE,&upLeft, &upRight, &downLeft, &downRight);

	//Instructing user and getting input.
	printf("\nThere can be 2-%d players in the game.\n", PLAYER_MAX);
	printf("How many players are there: ");
	scanf("%u", &n);		// Stores number of players in n

	/* Loop which ensures players number between 1 and defined player max (6) */
	while(n<2 || n>PLAYER_MAX)
	{
		puts("That number of players is invalid. Please enter a valid number of players.");
		scanf("%u", &n);	// Re-loops if incorrect number is entered
	}

	//Creating and initializing player struct for the number of players entered.
	struct player_type *player;
	player = calloc(n,sizeof(struct player_type));


	puts("\nA player's name can have a maximum length of 19 characters.");
	puts("There are 4 types of player: Elf, Human, Ogre and Wizard.");	//Giving information to user on the possible types of player_type and name specs.
	for(unsigned int i=0; i<n; i++)
	{
		//Function to get player details and initialize the player struct correctly
		playerInitialization(board, player, i);
	}
	/* MAIN GAME FUNCTION */
	crossFire(board, player, n, playersOut);
	
	return 0;
}
