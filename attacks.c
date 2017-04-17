/*
 * attacks.c
 *
 *  Created on: 13 Apr 2017
 *      Author: Dónal
 */


#include <stdio.h>
#include "crossfireOperations.h"
#include "structs.h"	//Including the definition of the structs and playerQuit prototype.

void playerQuit(struct slot ** board,struct player_type * player);

//Function for when one player decides to attack another.
void nearAttack(struct player_type *attacker, struct player_type *attacked, struct slot ** board)
{
	if(attacked->strength <= 70)		//If the attacked players strength is less than or equal to 70 then the attacked player gets half
	{									//of their strength subtracted from their life points.
		attacked->lifepoints -= (0.5 * attacker->strength);
		if(attacked->lifepoints<=0)
		{
			printf("%s, player %d, has been killed by %s, player %d, and has been removed from play.\n",attacked->name,attacked->id,attacker->name,attacker->id);
			playerQuit(board, attacked);	//player has lost all LP so quit function called and player removed
		}
	}
	else if(attacked->strength > 70)	//If the attacked players strength is greater than 70 then the player who initiated the attack gets
	{									//three tenths of the attacked players strength taken from their lifepoints.
		attacker->lifepoints -= (0.3 * attacked->strength);
		if(attacker->lifepoints<=0)
		{
			printf("%s, player %d, has been killed by %s, player %d, and has been removed from play.\n",attacker->name,attacker->id,attacked->name,attacked->id);
			playerQuit(board, attacker);	//player has lost all LP so quit function called and player removed
		}
	}
}

//Function to execute a distantAttack
void distantAttack(struct player_type *attacker, struct player_type *attacked, struct slot ** board)
{
	float x = attacker->strength;
	if(attacker->dexterity > attacked->dexterity)		//If the attacked players strength is less than or equal to 70 then the attacked player gets half
	{									//of their strength subtracted from their life points.
		attacked->lifepoints -= (0.3 * x);
		if(attacked->lifepoints<=0)
		{
			printf("%s, player %d, has been killed by %s, player %d, and has been removed from play.\n",attacked->name,attacked->id,attacker->name,attacker->id);
			playerQuit(board, attacked);	//player has lost all LP so quit function called and player removed
		}	
	}
}

//Function to execute a magicAttack
void magicAttack(struct player_type *attacker, struct player_type *attacked, struct slot ** board)
{
	attacked->lifepoints -= (0.5 * attacker->magicskills)+(0.2 * attacker->smartness);
	if(attacked->lifepoints<=0)
	{
		printf("%s, player %d, has been killed by %s, player %d, and has been removed from play.\n",attacked->name,attacked->id,attacker->name,attacker->id);
		playerQuit(board, attacked);	//player has lost all LP so quit function called and player removed
	}
}
