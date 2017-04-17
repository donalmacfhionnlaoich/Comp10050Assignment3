/*
 * structs.h
 *
 *  Created on: 4 Mar 2017
 *      Author: Dónal
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_
 
/* PLAYER STRUCT */
struct player_type {
	char name[20];		//Player name
	char type[20];		//Player type
	float lifepoints;	//Player lifepoints
	int smartness;		//Smartness value
	int strength;		//Strength value
	int magicskills;	//magicSkills value
	int luck;			//luck value
	int dexterity;		//dexterity value
	int row;			//row value
	int column;			//column value
	int id;				//id value
	int nearCheck, distantCheck, magicCheck;	//attack checks
};

#endif /* STRUCTS_H_ */
