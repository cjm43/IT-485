/*create entity*/
/*
#include "object.h"
#include "simple_logger.h"
#include "particle.h"

static Entity *__entity_list = NULL;
static int __entity_max = 0;
static int __entity_initialized = 0;

static void entity_deinitialize();

void entity_init(int maxEntity)
{
    if (__entity_initialized)
    {
        slog("already initialized");
        return;
    }
    __entity_list = (Entity *)malloc(sizeof(Entity)*maxEntity);
    memset(__entity_list,0,sizeof(Entity)*maxEntity);
    __entity_max = maxEntity;
    __entity_initialized = 1;
    slog("initialized %i entities",maxEntity);
    atexit(entity_deinitialize);
}

static void entity_deinitialize()
{
    int i;
    for (i = 0;i < __entity_max;i++)
    {
        if (__entity_list[i].inuse)
        {
            entity_free(&__entity_list[i]);
        }
    }
    free(__entity_list);
    __entity_max = 0;
    __entity_initialized = 0;
}

void entity_free(Entity *ent)
{
    if (!ent)
    {
        slog("passed a null entity");
        return;
    }
    ent[0].inuse = 0;
    obj_free(ent->objModel);
    FreeSprite(ent->texture);
}

Entity *entity_new()
{
    int i;
    for (i = 0; i < __entity_max;i++)
    {
        if (!__entity_list[i].inuse)
        {
            memset(&__entity_list[i],0,sizeof(Entity));
            __entity_list[i].inuse = 1;
            vec3d_set(__entity_list[i].scale,1,1,1);
			__entity_list[i].hidden = 0;
            vec4d_set(__entity_list[i].color,1,1,1,1);
            return &__entity_list[i];
        }
    }
    return NULL;
}

void entity_draw_all(Uint8 using_camera)
{
    int i;
    for (i = 0;i < __entity_max;i++)
    {
        if (__entity_list[i].inuse //if entity is in use
			&& !__entity_list[i].hidden //not hidden
			&&((!using_camera == __entity_list[i].camera_independent) || (!using_camera == __entity_list[i].camera_independent))) //and not using camera is equal to entity in list is camera independent 
        {
            entity_draw(&__entity_list[i]);
        }
    }
}

void entity_draw(Entity *ent)
{
    if (!ent)
    {
        return;
    }
	switch(ent->type)
	{
	case ENTITYTYPE_PARTICLE:
	    particle_draw(ent->position, ent->scale, ent->texture, 16);
		break;

	default:
		obj_draw(
			ent->objModel,
			ent->body.position,
			ent->rotation,
			ent->scale,
			ent->color,
			ent->texture
		);
		break;
	}
}

int entity_is_entity(void *data)
{
    if (!data)return 0;
    if (!__entity_initialized)return 0;
    if ((Entity *)data < __entity_list)return 0;
    if ((Entity *)data >= (__entity_list + __entity_max))return 0;
    return 1;
}


/*eol@eof*/

/*#include <stdio.h>//standard input/output
#include "entity.h"
#include <math.h>
#include "Collision.h"
#include "simple_logger.h"
#define MAX_ENTITY 1000

Entity entitylist[MAX_ENTITY]; //array of entites set to max number of entities


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
					 entitylist[i].rotation , //rotate
					 vec3d(1,1,1), //scale
					 vec4d(1,1,1,1), //color
					 entitylist[i].sprite);
		}
	}
}


void updateEntities()  // add the entity velocity to position and check for collision
{
	int i;
	for(i=0; i < MAX_ENTITY; i++)
	{
		if(entitylist[i].refcount!=0)//if entitylist refcount is not 0, entity is in use
		{
			entitylist[i].rotation.x = entitylist[i].rotation.x+1;
		}
	}
	
}
*/

