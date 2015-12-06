/**
 * gametest3d
 * @license The MIT License (MIT)
 *   @copyright Copyright (c) 2015 EngineerOfLies
 *    Permission is hereby granted, free of charge, to any person obtaining a copy
 *    of this software and associated documentation files (the "Software"), to deal
 *    in the Software without restriction, including without limitation the rights
 *    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the Software is
 *    furnished to do so, subject to the following conditions:
 *    The above copyright notice and this permission notice shall be included in all
 *    copies or substantial portions of the Software.
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *    SOFTWARE.
 */
#include "mgl_callback.h"
#include "simple_logger.h"
#include "graphics3d.h"
#include "shader.h"
#include "obj.h"
#include "vector.h"
#include "sprite.h"
#include "entity.h"
#include "space.h"
#include  "math.h"

Entity *p1;  //create global entity with pointer to memory address of p1

#define PI 3.14159265
#define WEAPON_OFFSET .0625 //1 divided by 2(double it if going up)
Space *space;
Entity *player;
Entity *drone;
void set_camera(Vec3D position, Vec3D rotation);
int bbon = 0;

void touch_callback(void *data, void *context) //function for objects touching
{
    Entity *ent,*me,*other, *ammo, *health, *health2, *drone;
	//Space *space;
    Body *obody;
    if ((!data)||(!context))return;
	ent = (Entity *)data;
	//soldier1->body.velocity = vec3d(-soldier1->body.velocity.x,-soldier1->body.velocity.y,-soldier1->body.velocity.z);
	//player->body.velocity = vec3d(-player->body.velocity.x,-player->body.velocity.y,-player->body.velocity.z);
    obody = (Body *)context;
    if (entity_is_entity(obody->touch.data)) //if entites are touching
    {
        //ammo = (Entity *)obody->touch.data;
		//player = (Entity *)obody->touch.data;
		//health = (Entity *)obody->touch.data;
		//health2 = (Entity *)obody->touch.data;
		/*Health and ammo pickup disappear when touched*/
		//slog("touch 1");
		if(ent==player){   //if entity is player
			space_remove_body(space, obody);  //remove body of other object
			((Entity *)(obody->touch.data))->destroy=1; //setting obody as an entity and setting it to destroy
			//slog("touch 2");
		}
		//entity_free(ammo);
		//entity_free(health);  //removes entity model but not collision body
		//entity_free(health2);
		
		//space_free(space);
		//space_remove_body(space,&health->body);  //free body to remove collision

    }
    //slog("touching me.... touching youuuuuuuu");
}

void think_callback(void *data, void *context)
{
	Entity *ent;
	//Space *space;
    Body *obody;
    if ((!data)||(!context))return;
	ent = (Entity *)data;

	track_player(ent);
	ent->next_think = 4000;

}

//Entity *newSmoke(Vec3D position)//creates object
//{
//    Entity * ent;
//    ent = entity_new();
//    if (!ent)
//    {
//        return NULL;
//    }
//	ent->camera_independent = 1;
//    ent->objModel = obj_load("models/cube.obj");
//    ent->texture = LoadSprite("models/smoke.png",512,512);
//    vec3d_cpy(ent->body.position,position);
//	ent->rotation.x = 90;
//	ent->rotation.y = 180;
//	ent->scale.x = 0.5;
//	ent->scale.y = 0.5;
//	ent->scale.z = 0.5;
//    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
//    //sprintf(ent->name,"%s",name);
//    //mgl_callback_set(&ent->body.touch,touch_callback,ent);
//	ent->type = ENTITYTYPE_PARTICLE;
//    return ent;
//}

Entity *newCube(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    if((ent->objModel = obj_load("models/cube.obj"))==NULL)
	{
		entity_free(ent);
		return NULL;
	}
    ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	//ent->camera_independent = 1;
	ent->rotation.x = 90;
	ent->rotation.y = 180;
	ent->scale.x = 0.3;
	ent->scale.y = 0.3;
	ent->scale.z = 0.3;
    cube_set(ent->body.bounds,0,0,0,1,1,1); //set bounding box x,y,z,w,h,d
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newPlayer(Vec3D position)//creates object
{

    Entity * ent;
	char name[] = "player";
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
	p1=ent;
	 //ent->objModel = obj_load("models/cube.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    //ent->objModel = obj_load("models/player.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
	//ent->camera_independent = 1;
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 3;
	ent->scale.y = 3.5;
	ent->scale.z = 3;
    cube_set(ent->body.bounds,-1,-1,-1,3,3,3);
	sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
	ent->type=ENTITYTYPE_PLAYER;
    return ent;
}

//Entity *newAssault(Vec3D position)//creates object
//{
//    Entity * ent;
//    ent = entity_new();
//    if (!ent)
//    {
//        return NULL;
//    }
//    ent->objModel = obj_load("models/Player_Gun.obj");
//    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
//    vec3d_cpy(ent->body.position,position);
//	ent->rotation.x = 0;
//	ent->rotation.y = 90;
//	ent->rotation.z = 0;
//	ent->scale.x = 1;
//	ent->scale.y = 1;
//	ent->scale.z = 1;
//    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
//    //sprintf(ent->name,"%s",name);
//    mgl_callback_set(&ent->body.touch,touch_callback,ent);
//    return ent;
//}
//
//Entity *newPistol(Vec3D position)//creates object
//{
//    Entity * ent;
//    ent = entity_new();
//    if (!ent)
//    {
//        return NULL;
//    }
//    ent->objModel = obj_load("models/pistol.obj");
//    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
//    vec3d_cpy(ent->body.position,position);
//	ent->rotation.x = 0;
//	ent->rotation.y = -90;
//	//ent->rotation.z = 90;
//	ent->scale.x = 0.5;
//	ent->scale.y = 0.5;
//	ent->scale.z = 0.5;
//    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
//    //sprintf(ent->name,"%s",name);
//    mgl_callback_set(&ent->body.touch,touch_callback,ent);
//    return ent;
//}
//
//Entity *newShotgun(Vec3D position)//creates object
//{
//    Entity * ent;
//    ent = entity_new();
//    if (!ent)
//    {
//        return NULL;
//    }
//    ent->objModel = obj_load("models/shotgun.obj");
//    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
//    vec3d_cpy(ent->body.position,position);
//	ent->rotation.x = 0;
//	ent->rotation.y = -90;
//    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
//    //sprintf(ent->name,"%s",name);
//    mgl_callback_set(&ent->body.touch,touch_callback,ent);
//    return ent;
//}
//
//Entity *newSmg(Vec3D position)//creates object
//{
//    Entity * ent;
//    ent = entity_new();
//    if (!ent)
//    {
//        return NULL;
//    }
//    ent->objModel = obj_load("models/smg.obj");
//    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
//    vec3d_cpy(ent->body.position,position);
//	ent->rotation.x = 0;
//	ent->rotation.y = 90;
//	ent->scale.x = 0.7;
//	ent->scale.y = 0.7;
//	ent->scale.z = 0.7;
//    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
//    //sprintf(ent->name,"%s",name);
//    mgl_callback_set(&ent->body.touch,touch_callback,ent);
//    return ent;
//}

Entity *newHealth(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/health.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,1,1,3,4,4,4);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newHealth2(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/health.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,1,1,3,4,4,4);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newHealth3(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/health.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;ent->scale.x = 1.3;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,1,1,3,4,4,4);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newAmmo(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/ammo.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,1,1,3,4,4,4);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newAmmo2(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/ammo.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,1,1,3,4,4,4);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newAmmo3(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/ammo.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,1,1,3,4,4,4);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newAmmo4(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/ammo.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newAmmo5(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/ammo.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newAmmo6(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/ammo.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newAmmo7(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/ammo.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newAmmo8(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/ammo.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newAmmo9(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/ammo.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newAmmo10(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/ammo.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newAmmo11(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/ammo.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newAmmo12(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/ammo.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newAmmo13(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/ammo.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newAmmo14(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/ammo.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newAmmo15(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/ammo.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newDrone(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/drone.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 90;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
	mgl_callback_set(&ent->think,think_callback,ent);
	ent->next_think = 4000;
    return ent;
}

Entity *newDrone2(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/drone.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 180;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newDrone3(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/drone.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 180;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newDrone4(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/drone.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 190;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newDrone5(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/drone.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 190;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newTurret1(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    if((ent->objModel = obj_load("models/turret.obj"))==NULL)
	{
		entity_free(ent);
		return NULL;
	}
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newSoldier1(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    if((ent->objModel = obj_load("models/soldier.obj"))==NULL)
	{
		entity_free(ent);
		return NULL;
	}
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	//vec3d_cpy(ent->body.rotation,rotation);
	ent->rotation.x = 90;
	ent->rotation.y = 180;
	ent->scale.x = 3;
	ent->scale.y = 3;
	ent->scale.z = 3;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}


int main(int argc, char *argv[])
{
    int i;
	int current_time = 0;
	int last_time = 0;
    float r = 0;
    //Space *space;
    Entity *ent,*cube,*smoke,*current_weapon,*assault,*assault2, *pistol, *shotgun, *smg, *health, *health2, *health3, *ammo, *ammo2, *ammo3,*ammo4,*ammo5,*ammo6, *ammo7, *ammo8, *ammo9, *ammo10, *ammo11, *ammo12, *ammo13, *ammo14, *ammo15, *drone1, *drone2, *drone3, *drone4, *drone5;
    char bGameLoopRunning = 1;
    
    SDL_Event e;
    Obj *obj, *bgobj;
    Sprite /**texture,*/ *bgtext;
    
    init_logger("gametest3d.log");
    if (graphics3d_init(1024,768,1,"gametest3d",33) != 0)
    {
        return -1;
    }
    model_init();
    obj_init();
    entity_init(255);

	//obj = obj_load("models/cube.obj");
	//texture = LoadSprite("models/cube_text.png",1024,1024);
    
    bgobj = obj_load("models/maze.obj");
    bgtext = LoadSprite("models/Solid_blue.png",1024,1024);

	player = newPlayer(vec3d(100,-110,0.1));
	player->body.position = vec3d(100,-110,0.1); //set initial camera position
    player->rotation = vec3d(90,0,0);    //set initial rotation
	//player->camera_independent = 1;

	//smoke = newSmoke(vec3d(80,-20,2));
	
	cube = newCube(vec3d(1.3f,-2.0f,-3.0f));
	cube->camera_independent = 1;

	/*pistol = newPistol(vec3d(1.3f,-2.0f,-3.0f));
	assault = newAssault(vec3d(3.0f,-4.0f,-1.0f)); 
	shotgun = newShotgun(vec3d(0.0f,-3.0f,-4.0f));
	smg = newSmg(vec3d(1.5f,-3.0f,-6.0f));*/

	/*current_weapon = pistol;
	pistol->hidden = 0;
	pistol->camera_independent = 1;
	assault->hidden = 1;
	shotgun->hidden = 1;
	smg->hidden = 1;*/
	

	health = newHealth(vec3d(100,-90,-4));
	health2 = newHealth(vec3d(100,-80,-4));
	health3 = newHealth(vec3d(100,-70,-4));

	ammo = newAmmo(vec3d(100,-60,-5));    
	ammo2 = newAmmo(vec3d(100,-50,-5));  
	ammo3 = newAmmo(vec3d(100,-40,-5)); 
	ammo4 = newAmmo(vec3d(100,-30,-5)); 
	ammo5 = newAmmo(vec3d(100,-20,-5)); 
	ammo6 = newAmmo(vec3d(90,-20,-5)); 
	ammo7 = newAmmo(vec3d(80,-20,-5)); 
	ammo8 = newAmmo(vec3d(70,-20,-5)); 
	ammo9 = newAmmo(vec3d(60,-20,-5)); 
	ammo10 = newAmmo(vec3d(50,-20,-5)); 
	ammo11 = newAmmo(vec3d(40,-20,-5)); 
	ammo12 = newAmmo(vec3d(30,-20,-5)); 
	ammo13 = newAmmo(vec3d(20,-20,-5)); 
	ammo14 = newAmmo(vec3d(10,-20,-5)); 
	ammo15 = newAmmo(vec3d(40,-80,-5)); 

	drone1 = newDrone(vec3d(50,-60,-5),"drone"); //+forward/-back, -left/+right, +up/-down
	drone2 = newDrone2(vec3d(-100,-100,-5),"drone");
	drone3 = newDrone3(vec3d(-90,-20,-5),"drone");
    drone4 = newDrone4(vec3d(-90,0,-5),"drone");
	drone4 = newDrone4(vec3d(-10,90,-5),"drone");

    //turret1 = newTurret1(vec3d(-10,90,-3),"turret");
	/*turret2 = newTurret2(vec3d(135,100,-9.3),"turret");
	turret3 = newTurret3(vec3d(-45,-60,-9.3),"turret");
	turret4 = newTurret4(vec3d(-45,0,-9.3),"turret");
	turret5 = newTurret5(vec3d(-133,90,-9.3),"turret");
	turret6 = newTurret6(vec3d(-133,20,-9.3),"turret");
	turret7 = newTurret7(vec3d(-90,-159,-9.3),"turret");*/

	/*soldier1 = newSoldier1(vec3d(135,-150,-10.6),"soldier");
	soldier2 = newSoldier2(vec3d(135,-75,-10.6),"soldier");
	soldier3 = newSoldier3(vec3d(70,-150,-10.6),"soldier");
	soldier4 = newSoldier4(vec3d(5,-150,-10.6),"soldier");
	soldier5 = newSoldier5(vec3d(-47,85,-10.6),"soldier");
	soldier6 = newSoldier6(vec3d(-33,35,-10.3),"soldier");
	soldier7 = newSoldier7(vec3d(-120,-159,-10.6),"soldier");*/
    
    //cube2->body.velocity.x = -0.1; //move cube2 0.1 units left
	//health->body.velocity.y = -0.1;
	//health2->body.velocity.y = -0.1;
	//player->body.velocity.y = 0;
    
    space = space_new();
    space_set_steps(space,100);

	//space_add_body(space,&player->body);

	//space_add_body(space,&cube->body);

    /*space_add_body(space,&assault->body);
	space_add_body(space,&pistol->body);
    space_add_body(space,&shotgun->body);
	space_add_body(space,&smg->body);*/

	space_add_body(space,&player->body);

	space_add_body(space,&health->body);
	space_add_body(space,&health2->body);
	space_add_body(space,&health3->body);

	space_add_body(space,&ammo->body);
	space_add_body(space,&ammo2->body);
	space_add_body(space,&ammo3->body);
	space_add_body(space,&ammo4->body);
	space_add_body(space,&ammo5->body);
	space_add_body(space,&ammo6->body);
	space_add_body(space,&ammo7->body);
	space_add_body(space,&ammo8->body);
	space_add_body(space,&ammo9->body);
	space_add_body(space,&ammo10->body);
	space_add_body(space,&ammo11->body);
	space_add_body(space,&ammo12->body);
	space_add_body(space,&ammo13->body);
	space_add_body(space,&ammo14->body);
	space_add_body(space,&ammo15->body);

	/*space_add_body(space,&drone1->body);
	space_add_body(space,&drone2->body);
	space_add_body(space,&drone3->body);
	space_add_body(space,&drone4->body);*/

	/*space_add_body(space,&turret1->body);
	space_add_body(space,&turret2->body);
	space_add_body(space,&turret3->body);
	space_add_body(space,&turret4->body);
	space_add_body(space,&turret5->body);
	space_add_body(space,&turret6->body);
	space_add_body(space,&turret7->body);

	space_add_body(space,&soldier1->body);
	space_add_body(space,&soldier2->body);
	space_add_body(space,&soldier3->body);
	space_add_body(space,&soldier4->body);
	space_add_body(space,&soldier5->body);
	space_add_body(space,&soldier6->body);
	space_add_body(space,&soldier7->body);*/

    while (bGameLoopRunning)
    {
		last_time = current_time;  //last time is equal to current time
		current_time = SDL_GetTicks(); //get new current time
        for (i = 0; i < 100;i++)
        {
            space_do_step(space);
        }
		//player->body.velocity=vec3d(0,0,0);
        while ( SDL_PollEvent(&e) ) 
        {
            if (e.type == SDL_QUIT)
            {
                bGameLoopRunning = 0;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    bGameLoopRunning = 0;
                }
				else if (e.key.keysym.sym == SDLK_b)
				{
					bbon = 1;
				}
                else if (e.key.keysym.sym == SDLK_SPACE)//move camera up
                {
                    player->body.position.z++;
                }
                else if (e.key.keysym.sym == SDLK_z)//move camera down
                {
                    player->body.position.z-= 2;
                }
                else if (e.key.keysym.sym == SDLK_w)//move forward
                {
                    
                       player->body.velocity = vec3d(          //move player based on velocity
                            .4*-sin(player->rotation.z * DEGTORAD),
                            .4*cos(player->rotation.z * DEGTORAD),
                            0
                        );
                }
                else if (e.key.keysym.sym == SDLK_s)//move back
                {
                   
                   player->body.velocity = vec3d(
                            .4*sin(player->rotation.z * DEGTORAD),
                            .4*-cos(player->rotation.z * DEGTORAD),
                            0
                        );
                }
                else if (e.key.keysym.sym == SDLK_d)//move right
                {
                    
					player->body.velocity = vec3d(
                            .4*cos(player->rotation.z * DEGTORAD),
                            .4*sin(player->rotation.z * DEGTORAD),
                            0
                        );
                }
                else if (e.key.keysym.sym == SDLK_a)//move left
                {
                   
					player->body.velocity = vec3d(
                           .4*-cos(player->rotation.z * DEGTORAD),
                           .4*-sin(player->rotation.z * DEGTORAD),
                            0
                        );
                }
				 else if (e.key.keysym.sym == SDLK_e)//move left
                {
                   
					player->body.velocity = vec3d(
                           0,
                           0,
                           0
                        );
                }
                else if (e.key.keysym.sym == SDLK_LEFT)
                {
                    player->rotation.z += 20;
                }
                else if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    player->rotation.z -= 20;
                }
                else if (e.key.keysym.sym == SDLK_UP)
                {
                    player->rotation.x += 20;
                }
                else if (e.key.keysym.sym == SDLK_DOWN)
                {
                    player->rotation.x -= 20;
                }
            }

			/*player weapon switch. need to remove equipped weapon when switching*/
			//if (e.type == SDL_KEYDOWN){
			//	if (e.key.keysym.sym == SDLK_1){
			//		current_weapon->hidden = 1;
			//		pistol->hidden = 0;
			//		current_weapon = pistol;
	  //              pistol->camera_independent = 1;
			//		//space_add_body(space,&pistol->body);
			//		slog("pistol");
			//	}
			//	else if (e.key.keysym.sym == SDLK_2){
			//		current_weapon->hidden = 1;
			//		assault->hidden = 0;
			//		current_weapon = assault;
	  //              assault->camera_independent = 1;
			//		//space_add_body(space,&assault->body);
			//		slog("assault rifle");
			//	}
			//	else if (e.key.keysym.sym == SDLK_3){
			//		current_weapon->hidden = 1;
			//		smg->hidden = 0;
			//		current_weapon = smg;
	  //              smg->camera_independent = 1;
			//		//space_add_body(space,&smg->body);
			//		slog("smg");
			//	}
			//	else if (e.key.keysym.sym == SDLK_4){
			//		current_weapon->hidden = 1;
			//		shotgun->hidden = 0;
			//		current_weapon = shotgun;
	  //              shotgun->camera_independent = 1;
			//	   //space_add_body(space,&shotgun->body);
			//		slog("shotgun");
			//	}
			//}

			/*if mouse is moved*/

			//if (e.type == SDL_MOUSEMOTION){  //move based on window size (1024,768); set safe bounding box (512x384)
			//	if(e.motion.x < 412){       //if camera is less than 412 
			//		player->rotation.z += 3; //down
			//	}
			//	else if(e.motion.x > 612){
			//		player->rotation.z -= 3;//up
			//	}
			//	if(e.motion.y < 284){
			//		player->rotation.x += 3; //right
			//	}
			//	else if (e.motion.y > 484){
			//		player->rotation.x -= 3;  //left
			//	}
			//}

			/*if mouse button is pressed. If player fires, spawn bullet(cube) and move it forward*/
			//if (e.type == SDL_MOUSEBUTTONDOWN){
			//	cube = newCube(vec3d(                                            //create new cube
			//		player->body.position.x - WEAPON_OFFSET*cos(player->rotation.z*PI/180), //spawn cube in front of gun barrel
			//		player->body.position.y + WEAPON_OFFSET*sin(player->rotation.z*PI/180),
			//		player->body.position.z - WEAPON_OFFSET*16));//16; move bullet up/down
			//	space_add_body(space,&cube->body);
			//	cube->body.velocity.x = -11.9*sin(player->rotation.z*PI/180); //move cube from gun barrel based on rotation, keeps cube moving in center of gun barrel
			//	cube->body.velocity.y = 11.9*cos(player->rotation.z*PI/180);//11.9, move bullet based on camera rotation
			//	//cube->body.velocity.z = 10.9*cos(player->rotation.z*PI/180);
			//	//cube->camera_independent = 1;
			//	slog("fire");
			//}
        }

        graphics3d_frame_begin();
        
        glPushMatrix();

		entity_draw_all(0); //draw entities not depedent on camera weapons(enemies,level)

		set_camera(
			player->body.position,
            player->rotation );
        
        entity_draw_all(1);  //draw entities dependent on camera (gun,projectile)

		 obj_draw(
            bgobj,
            vec3d(0,0,-10),//0,0,-10
            vec3d(90,90,0),
            vec3d(15,15,15),//5,5,5
            vec4d(1,1,1,1),
            bgtext
        );

        if (r > 360)r -= 360;
        glPopMatrix();
        /* drawing code above here! */
        graphics3d_next_frame();

		entity_cleanup(); //function for clearing up entities
		entity_think(current_time-last_time);  //check how long it has been since the last time time was checked
   }
    return 0;
}

void destroy_body(Entity *ent, Space *space)  //destroy entity's body at the end of collision check
		{
			if(ent->destroy = 1){  //if entity is destroyed
				space_free(space); //remove space from game
			}
		}

void set_camera(Vec3D position, Vec3D rotation)
{
    glRotatef(-rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(-rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(-rotation.z, 0.0f, 0.0f, 1.0f);
    glTranslatef(-position.x,
                 -position.y,
                 -position.z);
}

//void hide_weapon(Entity* ent)//hide current weapon
//{
//	ent->hidden = 1;
//}

void track_player(Entity* ent) //chase player when in range
{
	/*if player gets in range*/
	/*follow until player is dead or out of range*/

	Vec3D distance;         //distance for drone
	Vec3D normalized;       //moves drone one step
	float magnitude_squared;  //squared value of magnitude
	float magnitude;        //square root of magnitude_squared; used to calculate 
	float speed = 3;        //drone speed

	distance.x = player->body.position.x - drone->body.position.x;  //player position minus drone position; calculation for drone moving to player
	distance.y = player->body.position.y - drone->body.position.y;
	distance.z = player->body.position.z - drone->body.position.z; 

	magnitude_squared = pow (distance.x,2)+pow(distance.y,2)+pow(distance.z,2); //calculate magnitude_squared by squaring distance
	
    if(magnitude_squared<= 9)  //if drone's position minus player position squared is less than enemy range squared
	{
		magnitude = sqrt(magnitude_squared);    //magnitude is equal to square root of magnitude_squared
		normalized.x = distance.x/(magnitude);  //distance divided by magnitude to find how many steps drone should move
		normalized.y = distance.y/(magnitude);
		normalized.z = distance.z/(magnitude);
		drone->body.velocity.x = normalized.x * speed; //drone movement calculated by normalized value multiplied by speed
		drone->body.velocity.x = normalized.y * speed;
		drone->body.velocity.x = normalized.z * speed;
	}
}

/*keep track of player score*/
void score()
{

}

/*eol@eof*/