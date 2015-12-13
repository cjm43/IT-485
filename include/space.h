#ifndef __SPACE_H__
#define __SPACE_H__

#include "body.h"

typedef struct Space_S Space;


Space *space_new();

void space_free(Space *space);  //free up space in game;  free up memory for computer
void space_set_steps(Space *space,int steps);  //
void space_do_step(Space *space);              //check number of steps until objects collide
void space_add_body(Space *space,Body *body);  //add body to object
void space_remove_body(Space *space,Body *body); //remove body from game

#endif