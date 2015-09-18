#include <stdio.h>//standard input/output
#include "entity.h"
#include <math.h>
#define MAX_ENTITY 1000

Entity entitylist[MAX_ENTITY];

Entity *newEntity()
{
	int i;
	for(i=0; i < MAX_ENTITY; i++)
	{
		if(entitylist[i].refcount==0)//if entitylist refcount is 0, no entity is in use
		{
			entitylist[i].refcount++; //increments refcount, entity is in use
			return &entitylist[i];  //sends back location in memory where entity is
		}
	}
	fprintf(stderr,"error no entity \n");
	return NULL;
}


void destroyEntity(Entity *e)
{
	if(e < entitylist || e > &entitylist[MAX_ENTITY - 1]) //if address comes before entity list or after 
	{
		fprintf(stderr,"error destroyentity called but not an entity \n");
		return;
	}
	e->refcount--; //entity is part of list and decrease refcount
	return;
}

void initEntities() //initialize entity
{
	memset(entitylist,0,sizeof(Entity)* MAX_ENTITY);//resets all data in entitylist to 0
}

void drawEntities() // draw each entity's obj
{
	int i;
	for(i=0; i < MAX_ENTITY; i++)
	{
		if(entitylist[i].refcount!=0)//if entitylist refcount is not 0, entity is in use
		{
			obj_draw(entitylist[i].model,  //create data about object
					 entitylist[i].position,
					 vec3d(0,0,0) , //rotate
					 vec3d(1,1,1), //scale
					 vec4d(1,1,1,1), //color
					 entitylist[i].sprite);
		}
	}
}
void updateEntities()  // add the entity velocity to position and check for collision
{
	
 
}
