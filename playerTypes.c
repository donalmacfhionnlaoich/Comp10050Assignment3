/*
 * playerTypes.c
 *
 *  Created on: 4 Mar 2017
 *      Author: D�nal
 */

#include "crossfireOperations.h"
#include "structs.h"	//Including the definitions of structs.
#include <stdlib.h>		//Including prototypes of functions.

//Function to assign attributes of human player type to player.
void human(struct player_type *player, struct slot **board){
	int attrib[5], sum, i;		//Integer array to hold 5 attribute values. Declaring sum to keep a total of the sum of all elements assigned to the 5 attributes. i is an indexing variable.

	do{										//Do while sum of all attributes is less than or equal to 300.
		sum = 0;							//Setting sum to 0.
		for(i=0; i<5; i++){					//For loop to iterate through all 5 attributes.
			attrib[i] = rand() % 100 + 1;	//Each attribute is assigned a random value from 1-100 inclusive.
			sum += attrib[i];				//After each attribute is given a value, that value is added to the sum total for the final check after the for loop is exited.
		}
	}while(sum >= 300);
											//If the do while loop is exited, the sum of all 5 attributes must be within the criteria of a human, the sum of several attributes not exceeding 300.
	player->smartness = attrib[0];			//Assigning value of attribute 0 to player's smartness.
	player->strength = attrib[1];			//Assigning value of attribute 1 to player's strength.
	player->magicskills = attrib[2];		//Assigning value of attribute 2 to player's magic skills
	player->luck = attrib[3];				//Assigning value of attribute 3 to player's luck.
	player->dexterity = attrib[4];			//Assigning value of attribute 4 to player's dexterity.
	player->row = rand() % BOARD_SIZE;
	player->column = rand() % BOARD_SIZE;
	board[player->row][player->column].occupied = true;
	board[player->row][player->column].playersPresent[player->id]=1;

	if(board[player->row][player->column].slot_type == cityType)
	{
		city(player);
	}
	else if(board[player->row][player->column].slot_type == hillType)
	{
		hill(player);
	}
}

//Function to assign attributes of ogre player type to player.
void ogre(struct player_type *player, struct slot **board){
	int attrib[2], sum;			//Integer array to hold 2 attribute values. Declaring sum to keep a total of the sum of both elements assigned to the 2 attributes.

	do{										//Do while sum of all attributes is less than 50.
		sum = 0;							//Setting sum to 0.
		attrib[0] = rand() % 21;			//Assigning random value less than or equal to 20 to attribute for smartness.
		attrib[1] = rand() % 51;			//Assigning random value from 0-100 for the ogre's luck attribute.
		sum = attrib[1] + attrib[0];		//Calculating sum of both attributes.
	}
	while(sum > 50);
											//Do while loop is exited as sum is less than 50.
	player->smartness = attrib[0];			//First attribute is assigned to player's smartness.
	player->luck = attrib[1];				//Second attribute is assigned to player's luck.
	player->strength = rand() % 21 + 80;	//Value 80-100 inclusive is assigned to strength of player.
	player->dexterity = rand() % 21 + 80;	//Value 80-100 inclusive is assigned to dexterity of player.
	player->magicskills = 0;				//Magic skills of player set to 0.
	player->row = rand() % BOARD_SIZE;
	player->column = rand() % BOARD_SIZE;
	board[player->row][player->column].occupied = true;
	board[player->row][player->column].playersPresent[player->id]=1;
}

//Function to assign attributes of wizard player type to player.
void wizard(struct player_type *player, struct slot **board){

	player->smartness = rand() % 11 + 90;	//Value 90-100 inclusive assigned to player's smartness.
	player->luck = rand() % 51 + 50;		//Value 50-100 inclusive assigned to player's luck.
	player->strength = rand() % 20 + 1;		//Value 1-20 inclusive assigned to player's strength.
	player->dexterity = rand() % 100 + 1;	//Value 1-100 inclusive assigned to player's dexterity.
	player->magicskills = rand() % 21 + 80;	//Value 80-100 inclusive assigned to player's magic skills.
	player->row = rand() % BOARD_SIZE;
	player->column = rand() % BOARD_SIZE;
	board[player->row][player->column].occupied = true;
	board[player->row][player->column].playersPresent[player->id]=1;
}

//Function to assign attributes of wizard player type to player.
void elf(struct player_type *player, struct slot **board){

	player->smartness = rand() % 31 + 70;	//Value 70-100 inclusive assigned to player's smartness.
	player->luck = rand() % 41 + 60;		//Value 60-100 inclusive assigned to player's luck.
	player->strength = rand() % 50 + 1;		//Value 1-50 inclusive assigned to player's strength.
	player->dexterity = rand() % 100 + 1;	//Value 1-100 inclusive assigned to player's dexterity.
	player->magicskills = rand() % 29 + 51;	//Value 50-80 non-inclusive assigned to player's magic skills.
	player->row = rand() % BOARD_SIZE;
	player->column = rand() % BOARD_SIZE;
	board[player->row][player->column].occupied = true;
	board[player->row][player->column].playersPresent[player->id]=1;
}
