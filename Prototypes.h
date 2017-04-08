/*
 * Prototypes.h
 *
 *  Created on: 7 Apr 2017
 *      Author: Dónal
 */

#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

/* PLAYER TYPES SLOTS */
void human(struct player_type *player, struct slot **board);
void ogre(struct player_type *player, struct slot **board);
void wizard(struct player_type *player, struct slot **board);
void elf(struct player_type *player, struct slot **board);

#endif /* PROTOTYPES_H_ */
