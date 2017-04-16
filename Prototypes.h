/*
 * Prototypes.h
 *
 *  Created on: 7 Apr 2017
 *      Author: Dónal
 */

#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

void printPlayersStatus(struct player_type *player, int n, struct slot ** board);

/* PLAYER TYPE ASSIGN FUNCTIONS */
void human(struct player_type *player, struct slot **board);
void ogre(struct player_type *player, struct slot **board);
void wizard(struct player_type *player, struct slot **board);
void elf(struct player_type *player, struct slot **board);

/* ATTACK FUNCTION */
void nearAttack(struct player_type *attacker, struct player_type *attacked, struct slot ** board);
void distantAttack(struct player_type *attacker, struct player_type *attacked, struct slot ** board);
void magicAttack(struct player_type *attacker, struct player_type *attacked, struct slot ** board);

/* SLOT ASSIGN FUNCTIONS */
void city(struct player_type player);
void hill(struct player_type player);

/* CHOICE CHECK FOR POSSIBLE MOVEMENTS AND MOVE EXECTION FUNCTIONS */
void playerMoveChoice(struct slot ** board, struct player_type * player, char *slotChoice, int n, int i);
void MoveSlot (struct slot ** board,struct player_type * player, const int numOfPlayers, int row, int column, int i);

/* FUNCTION TO REMOVE PLAYER FROM BOARD AND SET ALL RELATED VARIABLES TO NULL */
void playerQuit(struct slot ** board,struct player_type * player);

/* FUNCTION TO CHECK POSSIBILITIES FOR NEAR, DISTANT & MAGIC ATTACKS  */
void playerCheck(struct slot ** board, struct player_type * player, int * checkerD, int x, int * playersFound);

void playerInitialization(struct slot ** board, struct player_type * player,int i);



#endif /* PROTOTYPES_H_ */
