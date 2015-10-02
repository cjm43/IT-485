/*Setting up a play area for game*/
#include <stdlib.h>
#include "space.h"
#include "body.h"
#include "simple_logger.h"

#include <glib.h>

struct Space_S
{
    GList *bodylist; /**<hash map of all bodies in space*/
    int steps; //check for collision by updating game area one step at a time
    int stepstaken; //number of how many steps have been taken
    float stepFactor; //
};

Space *space_new()  //create new game area
{
    Space *space;   //pointer to address of space with type Space
    space = (Space *)calloc(1,sizeof(struct Space_S)); //allocate uninitialized memory with size of game area
    return space;
}

void space_set_steps(Space *space,int steps) //set up number of steps in game area
{
    if (!space)return;
    if (!steps)
    {
        slog("cannot support zero steps!");
        return;
    }
    space->steps = steps; //set steps to number of steps
    space->stepFactor = 1.0/steps; //set stepFactor to 1 divided by number of steps
}

void space_remove_body(Space *space,Body *body) //remove object from game area
{
    if (!space)return;  
    if (!body)return;
    space->bodylist = g_list_remove(space->bodylist,body);  //go through list of objects and remove specific object
}

void space_add_body(Space *space,Body *body) //add object to game area
{
    if (!space)return;
    if (!body)return;
    space->bodylist = g_list_append(space->bodylist,body); //go to list of objects and add one more 
}

static void space_body_update(Space *space,Body *body) //update objects in game area
{
    GList *it;  //list with a pointer to address of it
    Cube a,b;
    Body *other;
    Vec3D stepVector; //vector of 
    Vec3D stepOffVector; // 
    
    vec3d_scale(stepVector,body->velocity,space->stepFactor);  //
    vec3d_negate(stepOffVector,stepVector);  //
    
    vec3d_add(body->position,body->position,stepVector);
    
    vec3d_cpy(a,body->position); //copy the position of object and put it in a
    a.w = body->bounds.w; //a's bounding width
    a.h = body->bounds.h; //a's bounding height
    a.d = body->bounds.d; //a's bounding diameter
    vec3d_add(a,a,body->bounds); //add bounding box to object
    
    for (it = space->bodylist;it != NULL;it = g_list_next(it))
    {
        if (!it->data)continue;
        if (it->data == body)continue;
        /*check for collision*/
        other = (Body *)it->data;
        vec3d_cpy(b,other->position);
        b.w = other->bounds.w;
        b.h = other->bounds.h;
        b.d = other->bounds.d;
        vec3d_add(b,b,other->bounds);
        slog("doing body test");
        if (cube_cube_intersection(a,b))
        {
            /*call touch functions*/
            /*back the fuck off*/
            vec3d_add(body->position,body->position,stepOffVector); //add distance between a and b to check for intersection
        }
    }
}

static void space_update(Space *space)  //update the game area
{
    GList *it;  //list with pointer to address of it
    for (it = space->bodylist; it != NULL; it = g_list_next(it)) //
    {
        if (!it->data)continue;
        space_body_update(space,(Body*)it->data); //update game object that's in the game area
    }
}

void space_do_step(Space *space)
{
    if (!space)return;
    if (space->stepstaken == space->steps) //if stepstaken is equal to steps
    {
        space->stepstaken = 0; //set stepstaken to 0
    }
    /*run one iteration of space update*/
    space_update(space);
    /*for each body, update it a little*/
    space->stepstaken++;
}

void space_free(Space *space) //remove game area from memory
{
    if (!space)return;
    free(space);
}

/*eol@eof*/