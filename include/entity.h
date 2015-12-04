#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "obj.h"
#include "vector.h"
#include "sprite.h"
#include "Collision.h"
#include "body.h"
#define ENTITYTYPE_PLAYER 0
#define ENTITYTYPE_ENEMY 1
#define ENTITYTYPE_OBJECT 2
#define ENTITYTYPE_PARTICLE 3

typedef struct Entity_S
{
    int inuse;
    int uid;    /**<unique id of this entity*/
    int type;
	char name[128];
    Vec3D acceleration;
	//Vec3D position;
    Vec3D rotation;
    Vec3D scale;
	Vec3D velocity;
    Vec4D color;
    Obj *objModel;
    Sprite *texture;    /**<object texture*/
    Body body;
	MglCallback touch;
	Uint8 camera_independent; //create objects that are not dependent on camera
	Uint8 hidden; //hide entity
	Uint8 destroy; //destroy body
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