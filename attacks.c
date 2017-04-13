/*
 * attacks.c
 *
 *  Created on: 13 Apr 2017
 *      Author: Dónal
 */


#include "structs.h"	//Including the definition of the structs.

//Function for when one player decides to attack another.
void nearAttack(struct player_type *attacker, struct player_type *attacked)
{
	if(attacked->strength <= 70)		//If the attacked players strength is less than or equal to 70 then the attacked player gets half
	{									//of their strength subtracted from their life points.
		attacked->lifepoints -= (0.5 * attacker->strength);
	}
	else if(attacked->strength > 70)	//If the attacked players strength is greater than 70 then the player who initiated the attack gets
	{									//three tenths of the attacked players strength taken from their lifepoints.
		attacker->lifepoints -= (0.3 * attacked->strength);
	}
}

void distantAttack(struct player_type *attacker, struct player_type *attacked)
{
	if(attacker->dexterity > attacked->dexterity)		//If the attacked players strength is less than or equal to 70 then the attacked player gets half
	{									//of their strength subtracted from their life points.
		attacked->lifepoints -= (0.3 * attacker->strength);
	}
}

void magicAttack(struct player_type *attacker, struct player_type *attacked)
{
	attacked->lifepoints -= (0.5 * attacker->magicskills)+(0.2 * attacker->smartness);
}
