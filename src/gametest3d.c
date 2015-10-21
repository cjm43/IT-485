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
//#include "entity.h"
#include "space.h"
#include "object.h"
#include  "math.h"

void set_camera(Vec3D position, Vec3D rotation);

void touch_callback(void *data, void *context) //function for objects touching
{
    Entity *me,*other, *soldier1, *soldier2;
    Body *obody;
    if ((!data)||(!context))return;
    soldier1 = (Entity *)data;
	soldier1->body.velocity = vec3d(-soldier1->body.velocity.x,-soldier1->body.velocity.y,-soldier1->body.velocity.z);
    obody = (Body *)context;
    if (entity_is_entity(obody->touch.data)) //if entites are touching
    {
		/*have cube2 move right after touching cube1*/
        soldier2 = (Entity *)obody->touch.data;
        //slog("%s is ",other->name);
		/*Health and ammo pickup disappear when touched*/

		soldier2->body.velocity = vec3d(-soldier2->body.velocity.x,-soldier2->body.velocity.y,-soldier2->body.velocity.z); //move cube2 in opposite direction as soon as it collides with cube1
		
    }
    //slog("touching me.... touching youuuuuuuu");
}

Entity *newAssault(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/Player_Gun.obj");
    ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 180;
	ent->scale.x = 1;
	ent->scale.y = 1;
	ent->scale.z = 1;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newPistol(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/pistol.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 0.5;
	ent->scale.y = 0.5;
	ent->scale.z = 0.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newShotgun(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/shotgun.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newSmg(Vec3D position)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/smg.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 180;
	ent->scale.x = 0.7;
	ent->scale.y = 0.7;
	ent->scale.z = 0.7;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

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
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
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
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
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
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
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
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
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
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
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
	ent->rotation.y = 180;
	ent->scale.x = 1.5;
	ent->scale.y = 1.5;
	ent->scale.z = 1.5;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
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
    sprintf(ent->name,"%s",name);
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

Entity *newTurret1(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/turret.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = -90;
	ent->scale.x = 3;
	ent->scale.y = 3;
	ent->scale.z = 3;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newTurret2(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/turret.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 90;
	ent->scale.x = 3;
	ent->scale.y = 3;
	ent->scale.z = 3;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newTurret3(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/turret.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
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

Entity *newTurret4(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/turret.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
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

Entity *newTurret5(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/turret.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
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

Entity *newTurret6(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/turret.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
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

Entity *newTurret7(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/turret.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = -90;
	ent->scale.x = 3;
	ent->scale.y = 3;
	ent->scale.z = 3;
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
    ent->objModel = obj_load("models/soldier.obj");
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

Entity *newSoldier2(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/soldier.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	//vec3d_cpy(ent->body.rotation,rotation);
	ent->rotation.x = 90;
	ent->rotation.y = 0;
	ent->scale.x = 3;
	ent->scale.y = 3;
	ent->scale.z = 3;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newSoldier3(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/soldier.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	//vec3d_cpy(ent->body.rotation,rotation);
	ent->rotation.x = 90;
	ent->rotation.y = 160;
	ent->scale.x = 3;
	ent->scale.y = 3;
	ent->scale.z = 3;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newSoldier4(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/soldier.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	//vec3d_cpy(ent->body.rotation,rotation);
	ent->rotation.x = 90;
	ent->rotation.y = 90;
	ent->scale.x = 3;
	ent->scale.y = 3;
	ent->scale.z = 3;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newSoldier5(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/soldier.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	//vec3d_cpy(ent->body.rotation,rotation);
	ent->rotation.x = 90;
	ent->rotation.y = 70;
	ent->scale.x = 3;
	ent->scale.y = 3;
	ent->scale.z = 3;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newSoldier6(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/soldier.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	//vec3d_cpy(ent->body.rotation,rotation);
	ent->rotation.x = 90;
	ent->rotation.y = 90;
	ent->scale.x = 3;
	ent->scale.y = 3;
	ent->scale.z = 3;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newSoldier7(Vec3D position, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/soldier.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	//vec3d_cpy(ent->body.rotation,rotation);
	ent->rotation.x = 90;
	ent->rotation.y = 150;
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
    float r = 0;
    Space *space;
    Entity *assault,*pistol, *shotgun, *smg, *health, *health2, *health3, *ammo, *ammo2, *ammo3, *drone1, *drone2, *drone3, *drone4, *turret1, *turret2, *turret3, *turret4, *turret5, *turret6, *turret7, *soldier1, *soldier2, *soldier3, *soldier4, *soldier5, *soldier6, *soldier7;
    char bGameLoopRunning = 1;
    Vec3D cameraPosition = {130,-20,0.3}; //set initial camera position
    Vec3D cameraRotation = {90,0,90};    //set initial rotation
    SDL_Event e;
    Obj /**obj,*/ *bgobj;
    Sprite /**texture,*/ *bgtext;
    
    init_logger("gametest3d.log");
    if (graphics3d_init(1024,768,1,"gametest3d",33) != 0)
    {
        return -1;
    }
    model_init();
    obj_init();
    entity_init(255);

	//obj = obj_load("models/Player_Gun.obj");
	//texture = LoadSprite("models/cube_text.png",1024,1024);
    
    bgobj = obj_load("models/level.obj");
    bgtext = LoadSprite("models/mountain_text.png",1920,1080);
    
    assault = newAssault(vec3d(90,-20,-3)); //create cube with position and name
	pistol = newPistol(vec3d(90,-30,-1));
	shotgun = newShotgun(vec3d(90,-17,-3));
	smg = newSmg(vec3d(90,-35,-2));

	health = newHealth(vec3d(-5,-29,-6));
	health2 = newHealth(vec3d(-120,-95,-6));
	health3 = newHealth(vec3d(5,-122,-6));

	ammo = newAmmo(vec3d(20,60,-6));    
	ammo2 = newAmmo(vec3d(-60,100,-6));  
	ammo3 = newAmmo(vec3d(-60,-160,-6));  

	drone1 = newDrone(vec3d(-10,55,-1),"drone"); //+forward/-back, -left/+right, +up/-down
	drone2 = newDrone2(vec3d(-10,-90,1),"drone");
	drone3 = newDrone3(vec3d(-60,-80,1),"drone");
    drone4 = newDrone4(vec3d(-90,-50,1),"drone");

    turret1 = newTurret1(vec3d(75,-3,-9.3),"turret");
	turret2 = newTurret2(vec3d(135,100,-9.3),"turret");
	turret3 = newTurret3(vec3d(-45,-60,-9.3),"turret");
	turret4 = newTurret4(vec3d(-45,0,-9.3),"turret");
	turret5 = newTurret5(vec3d(-133,90,-9.3),"turret");
	turret6 = newTurret6(vec3d(-133,20,-9.3),"turret");
	turret7 = newTurret7(vec3d(-90,-159,-9.3),"turret");

	soldier1 = newSoldier1(vec3d(135,-150,-10.6),"soldier");
	soldier2 = newSoldier2(vec3d(135,-75,-10.6),"soldier");
	soldier3 = newSoldier3(vec3d(70,-150,-10.6),"soldier");
	soldier4 = newSoldier4(vec3d(5,-150,-10.6),"soldier");
	soldier5 = newSoldier5(vec3d(-47,85,-10.6),"soldier");
	soldier6 = newSoldier6(vec3d(-33,35,-10.3),"soldier");
	soldier7 = newSoldier7(vec3d(-120,-159,-10.6),"soldier");
    
    //cube2->body.velocity.x = -0.1; //move cube2 0.1 units left
	soldier1->body.velocity.y = 0.1;
	soldier2->body.velocity.y = -0.1;
    
    space = space_new();
    space_set_steps(space,100);
    
    space_add_body(space,&assault->body);
	space_add_body(space,&pistol->body);
	space_add_body(space,&shotgun->body);
	space_add_body(space,&smg->body);

	space_add_body(space,&health->body);
	space_add_body(space,&health2->body);
	space_add_body(space,&health3->body);

	space_add_body(space,&ammo->body);
	space_add_body(space,&ammo2->body);
	space_add_body(space,&ammo3->body);

	space_add_body(space,&drone1->body);
	space_add_body(space,&drone2->body);
	space_add_body(space,&drone3->body);
	space_add_body(space,&drone4->body);

	space_add_body(space,&turret1->body);
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
	space_add_body(space,&soldier7->body);

    while (bGameLoopRunning)
    {
        for (i = 0; i < 100;i++)
        {
            space_do_step(space);
        }
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
                else if (e.key.keysym.sym == SDLK_SPACE)//move camera up
                {
                    cameraPosition.z++;
                }
                else if (e.key.keysym.sym == SDLK_z)//move camera down
                {
                    cameraPosition.z-= 2;
                }
                else if (e.key.keysym.sym == SDLK_w)//move forward
                {
                    vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            -sin(cameraRotation.z * DEGTORAD),
                            cos(cameraRotation.z * DEGTORAD),
                            0
                        ));
					//cameraPosition.x -= 5;
                }
                else if (e.key.keysym.sym == SDLK_s)//move back
                {
                    vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            sin(cameraRotation.z * DEGTORAD),
                            -cos(cameraRotation.z * DEGTORAD),
                            0
                        ));
					//cameraPosition.x += 5;
                }
                else if (e.key.keysym.sym == SDLK_d)//move right
                {
                    vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            cos(cameraRotation.z * DEGTORAD),
                            sin(cameraRotation.z * DEGTORAD),
                            0
                        ));
					//cameraPosition.y += 5;
                }
                else if (e.key.keysym.sym == SDLK_a)//move left
                {
                    vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            -cos(cameraRotation.z * DEGTORAD),
                            -sin(cameraRotation.z * DEGTORAD),
                            0
                        ));
					//cameraPosition.y -= 5;
                }
                else if (e.key.keysym.sym == SDLK_LEFT)
                {
                    cameraRotation.z += 15;
                }
                else if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    cameraRotation.z -= 15;
                }
                else if (e.key.keysym.sym == SDLK_UP)
                {
                    cameraRotation.x += 15;
                }
                else if (e.key.keysym.sym == SDLK_DOWN)
                {
                    cameraRotation.x -= 15;
                }
            }

			/*if mouse is moved. NEED TO FIGURE OUT HOW TO TURN CAMERA*/

			/*if (e.type == SDL_MOUSEMOTION){
				if(e.motion.xrel){
					cameraRotation.x -= 1;
				}
				else if (e.motion.xrel){
					cameraRotation.x = 1;
				}
			}
			if (e.type == SDL_MOUSEMOTION){
				if(e.motion.yrel){
					cameraRotation.y -= 1;
				}
				else if (e.motion.yrel){
					cameraRotation.x = 1;
				}
			}*/

			/*if mouse button is pressed*/
			if (e.type == SDL_MOUSEBUTTONDOWN){
				assault = newAssault(vec3d(70,-20,-3));
				assault->body.velocity.y = -0.1; 
				slog("fire");
			}
        }

        graphics3d_frame_begin();
        
        glPushMatrix();
        set_camera(
            cameraPosition,
            cameraRotation);
        
        entity_draw_all();  
		/*obj_draw(
            obj,
            vec3d(0,0,0),
            vec3d(90,r++,0),
            vec3d(0.5,0.5,0.5),
            vec4d(1,1,1,1),
			texture
        );*/

        obj_draw(
            bgobj,
            vec3d(0,0,-10),
            vec3d(90,90,0),
            vec3d(5,5,5),
            vec4d(1,1,1,1),
            bgtext
        );
        
        if (r > 360)r -= 360;
        glPopMatrix();
        /* drawing code above here! */
        graphics3d_next_frame();
    } 
    return 0;
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

/*eol@eof*/



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
/*
#include "simple_logger.h"
#include "graphics3d.h"
#include "shader.h"
#include "obj.h"
#include "vector.h"
#include "sprite.h"
#include "entity.h"
#include <math.h>
void set_camera(Vec3D position, Vec3D rotation);
void spawncube(Vec3D position);


int main(int argc, char *argv[])
{
    GLuint vao;
    float r = 0;
    GLuint triangleBufferObject;
    char bGameLoopRunning = 1;
    Vec3D cameraPosition = {0,-10,0.3};
    Vec3D cameraRotation = {90,0,0};
    SDL_Event e;
    Obj *obj,*bgobj;
    Sprite *texture,*bgtext;
    const float triangleVertices[] = {
        0.0f, 0.5f, 0.0f, 1.0f,
        0.5f, -0.366f, 0.0f, 1.0f,
        -0.5f, -0.366f, 0.0f, 1.0f,
        //next part contains vertex colors
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f  
    }; //we love you vertices!
    
    init_logger("gametest3d.log");
    if (graphics3d_init(1024,768,1,"gametest3d",33) != 0)
    {
        return -1;
    }
    model_init();
    obj_init();
	initEntities();
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao); //make our vertex array object, we need it to restore state we set after binding it. Re-binding reloads the state associated with it.
    
    glGenBuffers(1, &triangleBufferObject); //create the buffer
    glBindBuffer(GL_ARRAY_BUFFER, triangleBufferObject); //we're "using" this one now
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW); //formatting the data for the buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind any buffers
    
    obj = obj_load("models/cube.obj");
    texture = LoadSprite("models/cube_text.png",1024,1024);

    bgobj = obj_load("models/mountainvillage.obj");
    bgtext = LoadSprite("models/mountain_text.png",1024,1024);
    
//    obj = obj_load("models/mountainvillage.obj");
    
    /*spawn cube in game
    spawncube(vec3d(0,5,0) //position
			 ); 
	spawncube(vec3d(2,5,2)
			  //vec3d(0,90,0)
		     );
	spawncube(vec3d(0,10,0));

    while (bGameLoopRunning)
    {
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
                else if (e.key.keysym.sym == SDLK_SPACE)
                {
                    cameraPosition.z++;
                }
                else if (e.key.keysym.sym == SDLK_z)
                {
                    cameraPosition.z--;
                }
                else if (e.key.keysym.sym == SDLK_w)
                {
                    vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            -sin(cameraRotation.z * DEGTORAD),
                            cos(cameraRotation.z * DEGTORAD),
                            0
                        ));
                }
                else if (e.key.keysym.sym == SDLK_s)
                {
                    vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            sin(cameraRotation.z * DEGTORAD),
                            -cos(cameraRotation.z * DEGTORAD),
                            0
                        ));
                }
                else if (e.key.keysym.sym == SDLK_d)
                {
                    vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            cos(cameraRotation.z * DEGTORAD),
                            sin(cameraRotation.z * DEGTORAD),
                            0
                        ));
                }
                else if (e.key.keysym.sym == SDLK_a)
                {
                    vec3d_add(
                        cameraPosition,
                        cameraPosition,
                        vec3d(
                            -cos(cameraRotation.z * DEGTORAD),
                            -sin(cameraRotation.z * DEGTORAD),
                            0
                        ));
                }
                else if (e.key.keysym.sym == SDLK_LEFT)
                {
                    cameraRotation.z += 1;
                }
                else if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    cameraRotation.z -= 1;
                }
                else if (e.key.keysym.sym == SDLK_UP)
                {
                    cameraRotation.x += 1;
                }
                else if (e.key.keysym.sym == SDLK_DOWN)
                {
                    cameraRotation.x -= 1;
                }

            }
        }

        graphics3d_frame_begin();
        
        glPushMatrix();
        set_camera(
            cameraPosition,
            cameraRotation);

        drawEntities();  //get draw data
		updateEntities(); //update entity for every loop

		/*spawncube(  //create cube
			 vec3d(3,5,0), //position
			 vec3d(90,r++,0) //rotation
		   );
  
        obj_draw(
            bgobj,
            vec3d(0,0,2),
            vec3d(90,90,0), //rotate ground
            vec3d(5,5,5),
            vec4d(1,1,1,1),
            bgtext
        );
        
        obj_draw(  //create cube
            obj,
            vec3d(0,0,0), //position
            vec3d(0,r++,0), //rotation indefinitely
            vec3d(0.5,0.5,0.5), //scale
            vec4d(1,1,1,1),
            texture
        );
        if (r > 360)r -= 360;
        glPopMatrix();
        /* drawing code above here! 
        graphics3d_next_frame();
    } 
    return 0;
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

void spawncube(Vec3D position, Vec3D rotation) //spawn cube function
{
	Entity *ent;  //new entity pointer with variable Entity
	ent = newEntity(); //ent gets newEntity function data

	if(ent != NULL)   //if there is an entity
	{
		ent->position=position;                     //entity is pointing to position
		ent->rotation=rotation;                     //entity points to rotation
		ent->model=obj_load("models/cube.obj");;    //entity is pointing to object cube
		ent->sprite= LoadSprite("models/cube_text.png",1024,1024);;  //entity is pointing to sprite texture
	}
}


*/
/*eol@eof*/

