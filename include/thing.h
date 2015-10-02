#ifndef __THING_H__
#define __THING_H__

#include "obj.h"
#include "vector.h"
#include "sprite.h"
#include "Collision.h"
#include "body.h"

typedef struct Thing_S
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
}Thing;

/**
 * @brief initialize the entity sub system
 * @param maxEntity the maximum number of simultaneously supported entities.
 */
void thing_init(int maxThing);

/**
 * @brief get a pointer to a new entity
 * @return NULL on no more entities or error,  a valid entity pointer otherwise
 */
Thing *thing_new();

/**
 * @brief draws all active entities
 */
void thing_draw_all();

/**
 * @brief draws an entity
 * @param ent the entity to draw
 */
void thing_draw(Thing *ent);

/**
 * @brief frees an entity
 */
void thing_free(Thing *ent);

#endif