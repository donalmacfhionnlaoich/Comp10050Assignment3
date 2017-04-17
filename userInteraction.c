/*
 * userInteraction.c

 *
 *  Created on: 29 Mar 2017
 *      Author: liliana
 */

#include "crossfireOperations.h"
#include "structs.h"
#include "Prototypes.h"
#include <stdio.h>
 
void crossFire(struct slot **board, struct player_type * player, int n, int playersOut){

//Global int to hold the number players who've been put out of the game by quiting/dying
	playersOut = 0;

	//Array to hold the number of players who've left the game
	int playersFound[PLAYER_MAX] = {0};

	//Variable used in checking if a player can perform a distant attack
	int checkerD;

	//Index variables and user choice variable
	int i, j, choice;
	char slotChoice;

	//Variable used to check if the choice made by the user is allowed
	int allowedChoice;
	int roundNum=0; //index

	//Variable to hold which turn it is out of the possible players turns
	int playerRound;

	do
	{
		printPlayersStatus(player, n, board);
		printf("\n\n-----ROUND %d-----\n", roundNum+1);
		playerRound = 0;
		for(int i=0;i<n;i++)	//Loop through players
		{
			playerRound++;
			if(player[i].lifepoints>0)	//If player is alive allow them to take their turn
			{
				//Printing which players turn it is and which player they are in out of the remaining alive players
				printf("\nPLAYER %d - %d / OF %d\n\n",i+1, playerRound, n-playersOut);
				if(playersOut>0){
					printf("%d player(s) died/left!\n\n",playersOut);
				}

				playerCheck(board, player, &checkerD, i, playersFound);	//Setting attack player's capabilities


				do{
					if(((player[i].magicCheck!=1)&&(player[i].distantCheck!=1)&&(player[i].nearCheck!=1)))
					{
						printf("Player %d, no other players in range!\n", i+1);
					}
					//Asking user for input on what action they would like to take
					printf("Would you like to:\n");
					//Only the options available to user are printed
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

					allowedChoice = 0;	//Resetting allowedChoice to 0 as the default
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
								puts("\nIncorrect number entered!\n");
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
								puts("\nIncorrect number entered!\n");
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
								puts("\nIncorrect number entered!\n");
							}
							break;
					}
				}while(choice != 1 && choice != 0 && allowedChoice !=1 );	//Continues unless move, quit or an allowed attack option is selected

				//Caries out chosen action
				switch(choice)
				{
					case 4:	//Magic attack
						//Loop to print all players alive since any alive player can be attacked
						for(j = 0;j<n;j++)
						{
							if(player[j].lifepoints>0 && j != i)
							{
								printf("%s can be attacked. ID = %d\n",player[j].name, j);
							}
						}
						//Asks player to input a player id to attack until a valid choice is made
						do{
							printf("Enter the ID number of the player you wish to attack: ");
							scanf("%d", &choice);
						}while(choice == i || player[choice].lifepoints<=0 || choice>=n || choice<0);

						//Alert of attack
						printf("\n\n**Attacking %s(%d) with a magic attack.**\n\n",player[choice].name,choice);
						//Calling magicAttack
						magicAttack( &player[i], &player[choice], board); //first arg is attacker, second is attacked
						break;

					case 3:	//Distant attack
						//Resetting playersFound array to 0
						for(j=0;j<PLAYER_MAX;j++)
						{
							playersFound[j]=0;
						}
						//Calling findSlots for distance 2, 3 & 4 to get all attackable players of distant attack
						for(j=2;j<5;j++)
						{
							findSlots(j, 0,  &board[player[i].row][player[i].column], playersFound, &checkerD, i);
						}
						//Printing all attackable players with distant attack.
						for(j=0;j<n;j++)
						{
							if(playersFound[j]==1)
							{
								printf("%s can be attacked. ID = %d\n",player[j].name, j);
							}
						}
						//Asks player to input a player id to attack until a valid choice is made
						do{
							printf("Enter the ID number of the player you wish to attack: ");
							scanf("%d", &choice);
						}while(choice>n || choice<0 || playersFound[choice]!=1);
						//Alert of attack
						printf("\n\n**Attacking %s(%d) with distant attack.**\n\n",player[choice].name,choice);
						//Call distantAttack
						distantAttack( &player[i], &player[choice], board);

						break;

					case 2:	//Near attack
						//Resetting playersFound array to 0
						for(j=0;j<PLAYER_MAX;j++)
						{
							playersFound[j]=0;
						}
						//Finding all attackable players with near attack
						checkNearAttack(board, player[i].row, player[i].column, i, playersFound);
						//Printing all attackable players with near attack
						for(j=0;j<n;j++)
						{
							if(playersFound[j]==1)
							{
								printf("%s can be attacked. ID = %d\n",player[j].name, j);
							}
						}
						//Asks player to input a player id to attack until a valid choice is made
						do{
							printf("Enter the ID number of the player you wish to attack: ");
							scanf("%d", &choice);
						}while(choice>n || choice<0 || playersFound[choice]!=1);
						//Alert of attack
						printf("\n\n**Attacking %s (ID: %d) with near attack.**\n\n",player[choice].name,choice);
						//Calling near attack
						nearAttack( &player[i], &player[choice], board);

						break;

					case 1:	//move slot
						playerMoveChoice(board, player, &slotChoice, n, i);
						break;
					case 0:	//quit
						playerQuit(board, &player[i]);
						break;
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
}
