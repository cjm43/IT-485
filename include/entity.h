#ifndef __ENTITY_H__
#define __ENTITY_H__
#include "Collision.h"
#include "obj.h"

typedef struct  //typedef-creating new variable type
{
	int refcount;  //keeps count of how many references are in use
	Vec3D position;
	Vec3D rotation;
	Obj *model;    //create model
	Sprite *sprite; //create texture
} Entity;

//function prototypes
void initEntities(); //initialisation
Entity *newEntity();//new entity
void destroyEntity(Entity *e);//kill when done
void drawEntities(); // draw each entity's obj
void updateEntities();// add the entity velocity to position and check for collision

void newBoxEntity(Vec3D position, Vec3D velocity);
#endif