#ifndef __BODY_H__
#define __BODY_H__

#include "vector.h"
#include "Collisions.h"

typedef struct
{
    Vec3D position;
    Vec3D velocity;
    Cube bounds;
    void *userData; /**<pointer back to the player*/
}Body;

#endif