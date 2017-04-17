/*
 * printPlayersStatus.c
 *
 *  Created on: 4 Mar 2017
 *      Author: Dónal
 */

#include "crossfireOperations.h"
#include "structs.h"	//Including definition of structs
#include <stdio.h>		//Including stdio library for printf function.

//Function to print out all details of every player.
void printPlayersStatus(struct player_type *player, int n, struct slot ** board)
{
	for(int i=0; i<n; ++i)	//For loop to index through each player up to the final player.
	{
		if(player[i].lifepoints>0)
		{
			printf("\n-PLAYER %d-\n", i+1);							//Indicating which player the following details are related to.
			printf("Name:\t\t%s\n", player[i].name);				//Printing player name.
			printf("Type:\t\t%s\n", player[i].type);				//Printing what type of player the selected player is.
			printf("Life Points:\t%.1f\n", player[i].lifepoints);	//Printing the value of the lifepoints of the player.
			printf("Smartness:\t%d\n", player[i].smartness);		//Printing the value of the smartness value of the player selected.
			printf("Strength:\t%d\n", player[i].strength);			//Printing the value of the strength of the selected player.
			printf("Magic Skills:\t%d\n", player[i].magicskills);	//Printing the value of the magic skills of the slected player.
			printf("Luck:\t\t%d\n", player[i].luck);				//Printing the value of the luck of the slected player.
			printf("Dexterity:\t%d\n", player[i].dexterity);		//Printing the value of the dexterity of the slected player.
			printf("Slot Name:\t%s\n", board[player[i].row][player[i].column].slot_name);		//Printing the slot type of the player.
			printf("Player ID:\t%d\n",player[i].id);				//Prints ID of player
			printf("Position:\t (%d,%d)\n",player[i].row,player[i].column);	//Prints players position on the board
		}
	}
}
