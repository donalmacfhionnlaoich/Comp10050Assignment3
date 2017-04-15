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
	srand(time(NULL));

	int row, column, i;

	struct slot* currSlot = NULL;
	struct slot *foundSlots = calloc((BOARD_SIZE*BOARD_SIZE), sizeof(struct slot));

	//int explored[BOARD_SIZE][BOARD_SIZE] = {false};
	bool *explored[BOARD_SIZE];
	for(i=0;i<BOARD_SIZE;i++)
	{
		explored[i] = calloc(BOARD_SIZE,sizeof(bool));
	}

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


		for(i =0; i< BOARD_SIZE; i++)
		{
			//This allocates in memory the space for the slots in each row of the board
			board[i] = calloc(BOARD_SIZE, sizeof(struct slot));
		}

	//Creates the board
	createBoard(board,BOARD_SIZE,&upLeft, &upRight, &downLeft, &downRight);

	unsigned int n, typeNum;
	printf("There can be 2-%d players in the game.\n", PLAYER_MAX);
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
	printPlayersStatus(player, n, board);
	playersOut = 0;
	int playersFound[PLAYER_MAX] = {0};

	/*for(i=2;i<5;i++)
	{
		findSlots(i, 0,  &board[player[0].row][player[0].column], foundSlots, &count, explored, playersFound);
		printf("%d Iteration\n", i-1);
	}
	for(i=0;i<PLAYER_MAX;i++)
	{
		printf("Player %d was found: %d\n", i, playersFound[i]);
	}*/
	//printPlayersStatus(player, n, board);
	int checkerD;
	int x, j, choice;
	char slotChoice;
	int allowedChoice;
	int ind; //index

	//For loop to iterate through all players
/*	for(x = 0; x<n;x++)
	{
		PLAYER ROUND*/
		//Checking that the player is alive
		/*if(player[x].lifepoints>0)
		{
			playerCheck(board, player, &checkerD, x, playersFound);	//Setting player's capabilities
		}
	}*/


	do
	{
		for(int i=0;i<n;i++)	//Loop through players
		{
			printPlayersStatus(player, n, board);

			printf("PLAYER %d",i);
			if(player[i].lifepoints>0)	//If player is alive
			{

				playerCheck(board, player, &checkerD, i, playersFound);	//Setting player's capabilities

				//If player cannot attack any other player.
				if(((player[i].magicCheck!=1)&&(player[i].distantCheck!=1)&&(player[i].nearCheck!=1)))
				{
					do{
						printf("Player %d, no other players in range!\n", i+1);
						printf("Would you like to:\n");
						printf("1 - Move to an adjacent slot\n");
						printf("0 - Quit the game\n");
						fflush(stdin);
						scanf("%d", &choice);
					}while(choice != 1 && choice != 0);
					switch(choice)
					{
						case 1:
							playerMoveChoice(board, player, &slotChoice, n, i);

							/*
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
								scanf(" %c", &slotChoice);
								switch(slotChoice)
								{
									case 'u':
										if((board[player[i].row][player[i].column].up)!=NULL){
											MoveSlot(board, player[i], n, player[i].row+1, player[i].column);
											break;
										}
										else{
											printf("Incorrect value entered! case u\n");
											slotChoice = -1;
										}
									case 'd':
										if((board[player[i].row][player[i].column].down)!=NULL){
											MoveSlot(board, player[i], n, player[i].row-1, player[i].column);
											break;
										}
										else{
											printf("Incorrect value entered! case d\n");
											slotChoice = -1;
										}
									case 'l':
										if((board[player[i].row][player[i].column].left)!=NULL){
											MoveSlot(board, player[i], n, player[i].row, player[i].column-1);
											break;
										}
										else{
											printf("Incorrect value entered! case l\n");
											slotChoice = -1;
										}
									case 'r':
										if((board[player[i].row][player[i].column].right)!=NULL){
											MoveSlot(board, player[i], n, player[i].row, player[i].column+1);
											break;
										}
										else{
											printf("Incorrect value entered! case r\n");
											slotChoice = -1;
										}
									default:
										printf("Incorrect value entered! default\n");
										slotChoice = -1;
										break;
								}
							}while(slotChoice==-1); //why??*/
							break;
						case 0:
							playerQuit(board, &player[i]);
							break;
					}
				}
				else if(((player[i].magicCheck==1)||(player[i].distantCheck==1)||(player[i].nearCheck==1)))
				{
					do{

						//printf("Player %d, no other players in range!\n", i+1);
						printf("Would you like to:\n");
						if(player[i].magicCheck==1)
						{
							puts("4 - Attack a player with a magic attack");
						}
						if(player[i].distantCheck==1)
						{
							puts("3 - Attack a distant player");
						}
						if(player[i].nearCheck==1)
						{
							puts("2 - Attack a nearby player");
						}
						printf("1 - Move to an adjacent slot\n");
						printf("0 - Quit the game\n");
						fflush(stdin);
						scanf("%d", &choice);
						allowedChoice = 0;
						//Checking input if allowed for attacks.
						switch(choice)
						{
							case 2:
								if(player[i].nearCheck==1)
								{
									allowedChoice = 1;
								}
								else
								{
									allowedChoice = 0;
								}
								break;
							case 3:
								if(player[i].distantCheck==1)
								{
									allowedChoice = 1;
								}
								else
								{
									allowedChoice = 0;
								}
								break;
							case 4:
								if(player[i].magicCheck==1)
								{
									allowedChoice = 1;
								}
								else
								{
									allowedChoice = 0;
								}
								break;
						}
					}while(choice != 1 && choice != 0 && allowedChoice !=1 );
					switch(choice)
					{
						case 4:
							for(ind = 0;ind<n;ind++)
							{
								if(player[ind].lifepoints>0 && ind != i)
								{
									printf("%s can be attacked. ID = %d\n",player[ind].name, ind);
								}
							}
							do{
								printf("Enter the ID number of the player you wish to attack: ");
								scanf("%d", &choice);
							}while(choice == i || player[choice].lifepoints<=0 || choice>=n || choice<0);
							printf("Attacking %s(%d) with a magic attack.\n",player[choice].name,choice);
							magicAttack( &player[i], &player[choice], board); //first ard is attacker, second is attacked
							break;

						case 3:
							//Resetting playersFOund array to 0
							for(j=0;j<PLAYER_MAX;j++)
							{
								playersFound[j]=0;
							}
							for(j=2;j<5;j++)
							{
								findSlots(j, 0,  &board[player[i].row][player[i].column], playersFound, &checkerD, i);
							}
							for(j=0;j<n;j++)
							{
								if(playersFound[j]==1)
								{
									printf("%s can be attacked. ID = %d\n",player[j].name, j);
								}
							}
							do{
								printf("Enter the ID number of the player you wish to attack: ");
								scanf("%d", &choice);
							}while(choice>n || choice<0 || playersFound[choice]!=1);
							printf("Attacking %s(%d) with distant attack.\n",player[choice].name,choice);
							distantAttack( &player[i], &player[choice], board);

							break;

						case 2:
							for(i=0;i<PLAYER_MAX;i++)
							{
								playersFound[i]=0;
							}
							checkNearAttack(board, player[i].row, player[i].column, i, playersFound);
							for(j=0;j<n;j++)
							{
								if(playersFound[j]==1)
								{
									printf("%s can be attacked. ID = %d\n",player[j].name, j);
								}
							}
							do{
								printf("Enter the ID number of the player you wish to attack: ");
								scanf("%d", &choice);
							}while(choice>n || choice<0 || playersFound[choice]!=1);

							printf("Attacking %s(%d) with near attack.\n",player[choice].name,choice);
							nearAttack( &player[i], &player[choice], board);

							break;

						case 1:
							playerMoveChoice(board, player, &slotChoice, n, i);
							//playerMoveChoice( board, player, &slotChoice, n, i);
						/*	printf("What slot would you like to move to:\n");
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
								scanf(" %c", &slotChoice);
								switch(slotChoice)
								{
									case 'u':
										if((board[player[i].row][player[i].column].up)!=NULL){
											MoveSlot(board, player[i], n, player[i].row+1, player[i].column);
											break;
										}
										else{
											printf("Incorrect value entered! case u\n");
											slotChoice = -1;
										}
									case 'd':
										if((board[player[i].row][player[i].column].down)!=NULL){
											MoveSlot(board, player[i], n, player[i].row-1, player[i].column);
											break;
										}
										else{
											printf("Incorrect value entered! case d\n");
											slotChoice = -1;
										}
									case 'l':
										if((board[player[i].row][player[i].column].left)!=NULL){
											MoveSlot(board, player[i], n, player[i].row, player[i].column-1);
											break;
										}
										else{
											printf("Incorrect value entered! case l\n");
											slotChoice = -1;
										}
									case 'r':
										if((board[player[i].row][player[i].column].right)!=NULL){
											MoveSlot(board, player[i], n, player[i].row, player[i].column+1);
											break;
										}
										else{
											printf("Incorrect value entered! case r\n");
											slotChoice = -1;
										}
									default:
										printf("Incorrect value entered! default\n");
										slotChoice = -1;
										break;
								}
							}while(slotChoice==-1);*/
							break;
						case 0:
							playerQuit(board, &player[i]);
							break;
					}
				}
				//printf("n is %d & out is %d",n,playersOut);
				if(n-1<=playersOut)
				{
					//printf("breaking");
					break;
				}
			}
		}
	}while(n-1>playersOut);


	if(n>playersOut)
	{
		for(i=0;i<n;i++)
		{
			if(player[i].lifepoints>0)
			{
				printf("%s has won the game! GG",player[i].name);
				break;
			}
		}
	}
	else
	{
		puts("It appears all players are dead. GG");
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
