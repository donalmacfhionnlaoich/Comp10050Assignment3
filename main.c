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
	printf("\nThere can be 2-%d players in the game.\n", PLAYER_MAX);
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
		playerInitialization(board, player, i);
	}
	playersOut = 0;
	int playersFound[PLAYER_MAX] = {0};
	int checkerD;
	int x, j, k, choice;
	char slotChoice;
	int allowedChoice;
	int ind, roundNum=0; //index
	int playerRound;

	do
	{	printPlayersStatus(player, n, board);
		printf("\n\n-----ROUND %d-----\n", roundNum+1);
		playerRound = 0;
		for(int i=0;i<n;i++)	//Loop through players
		{
			playerRound++;
			if(player[i].lifepoints>0)	//If player is alive
			{
				printf("\nPLAYER %d / OF %d\n\n",playerRound, n-playersOut);
				if(playersOut>0){
					printf("%d player(s) died/left!\n\n",playersOut);
				}
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
							break;
						case 0:
							playerQuit(board, &player[i]);
							break;
					}
				}
				else if(((player[i].magicCheck==1)||(player[i].distantCheck==1)||(player[i].nearCheck==1)))
				{
					do{
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
							for(k=0;k<PLAYER_MAX;k++)
							{
								playersFound[k]=0;
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

							printf("Attacking %s (ID: %d) with near attack.\n",player[choice].name,choice);
							nearAttack( &player[i], &player[choice], board);

							break;

						case 1:
							playerMoveChoice(board, player, &slotChoice, n, i);
							break;
						case 0:
							playerQuit(board, &player[i]);
							break;
					}
				}
				if(n-1<=playersOut)
				{
					break;
				}
			}
			else
			{
				playerRound--; //Decrementing playerRound number so that correct number is displayed
			}
		}
		roundNum++;
	}while(n-1>playersOut);

	if(n>playersOut)
	{
		for(i=0;i<n;i++)
		{
			if(player[i].lifepoints>0)
			{
				printf("\n%s has won the game! GG\n\n",player[i].name);
				break;
			}
		}
	}
	else
	{
		puts("\nIt appears all players are dead. GG\n\n");
	}
	return 0;
}
