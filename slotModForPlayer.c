/*
 * slotModForPlayer.c
 *
 *  Created on: 4 Mar 2017
 *      Author: D�nal
 */

#include "structs.h"	//Including definition of structs.

//Function to change a player's attributes if it is on a city slot.
void city(struct player_type * player)
{
	if(player->smartness > 60)			//If player's smartness is greater than 60, increase their magic skills by 10 points.
	{
		if(player->magicskills >= 90)		//Max value for magicskills is 100. If player's magicskills is greater than or equal to 90 then set the player's magicskills to 100.
		{
			player->magicskills = 100;		//Assigning 100 to player's magic skills.
		}
		else if(player->magicskills < 90)	//If player's magic skills is less than 90, add 10 to their magic skills.
		{
			player->magicskills += 10;		//Adding 10 to the player's magic skills.
		}
	}
	else if(player->smartness <= 50)	//If player's smartness is less than or equal to 50, subtract 10 from their dexterity.
	{
		if(player->dexterity <= 10)			//Minimum value is 0. If player's dexterity is less than or equal to 10 then set dexterity to 0.
		{
			player->dexterity = 0;			//Assigning 0 to player's dexterity.
		}
		else if(player->dexterity > 10)		//If player's dexterity is greater than 10, subtract 10 from the player's dexterity.
		{
			player->dexterity -= 10;		//Subtracting 10 from player's dexterity.
		}
	}
}

//Function to change a player's attributes if it is on a hill slot.
void hill(struct player_type * player)
{
	if(player->dexterity >= 60)			//If player's dexterity is greater than or equal to 60, add 10 to their strength.
	{
		if(player->strength >= 90)			//Max value for strength is 100. If player's strength is greater than or equal to 90 then set the player's strength to 100.
		{
			player->strength = 100;			//Assigning 100 to player's strength.
		}
		else if(player->strength < 90)		//If player's strength is less than 90, add 10 to their strength.
		{
			player->strength += 10;			//Adding 10 to the player's strength.
		}
	}
	else if(player->dexterity < 50)		//If player's dexterity is less than 50, subtract 10 from their dexterity.
	{
		if(player->strength <= 10)		//Minimum value is 0. If player's strength is less than or equal to 10 then set strength to 0.
		{
			player->strength = 0;		//Assigning 0 to player's strength.
		}
		else if(player->strength > 10)	//If player's strength is greater than 10, subtract 10 from the player's strength.
		{
			player->strength -= 10;		//Subtracting 10 from player's strength.
		}
	}
}
