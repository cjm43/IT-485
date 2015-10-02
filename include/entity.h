/*#ifndef __ENTITY_H__
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

*/

#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "obj.h"
#include "vector.h"
#include "sprite.h"
#include "Collision.h"
#include "body.h"

typedef struct Entity_S
{
    int inuse;
    int uid;    /**<unique id of this entity*/
    char name[128];
    Vec3D acceleration;
    Vec3D rotation;
    Vec3D scale;
    Vec4D color;
    Obj *objModel;
    Sprite *texture;    /**<object texture*/
    Body body;
}Entity;

/**
 * @brief initialize the entity sub system
 * @param maxEntity the maximum number of simultaneously supported entities.
 */
void entity_init(int maxEntity);

/**
 * @brief get a pointer to a new entity
 * @return NULL on no more entities or error,  a valid entity pointer otherwise
 */
Entity *entity_new();

/**
 * @brief draws all active entities
 */
void entity_draw_all();

/**
 * @brief draws an entity
 * @param ent the entity to draw
 */
void entity_draw(Entity *ent);

/**
 * @brief frees an entity
 */
void entity_free(Entity *ent);

int entity_is_entity(void *data);

#endif