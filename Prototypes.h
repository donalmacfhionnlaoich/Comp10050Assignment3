/*
 * Prototypes.h
 *
 *  Created on: 7 Apr 2017
 *      Author: Dónal
 */

#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

void printPlayersStatus(struct player_type *player, int n, struct slot ** board);

/* PLAYER TYPES SLOTS */
void human(struct player_type *player, struct slot **board);
void ogre(struct player_type *player, struct slot **board);
void wizard(struct player_type *player, struct slot **board);
void elf(struct player_type *player, struct slot **board);

void nearAttack(struct player_type *attacker, struct player_type *attacked);
void distantAttack(struct player_type *attacker, struct player_type *attacked);
void magicAttack(struct player_type *attacker, struct player_type *attacked);

void city(struct player_type player);
void hill(struct player_type player);

void MoveSlot (struct slot ** board,struct player_type player, const int numOfPlayers, int row, int column);
void playerQuit(struct slot ** board,struct player_type player);

#endif /* PROTOTYPES_H_ */
