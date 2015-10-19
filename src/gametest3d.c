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
    Entity *me,*other;
    Body *obody;
    if ((!data)||(!context))return;
    me = (Entity *)data;
	me->body.velocity = vec3d(-me->body.velocity.x,-me->body.velocity.y,-me->body.velocity.z);
    obody = (Body *)context;
    if (entity_is_entity(obody->touch.data)) //if entites are touching
    {
		/*have cube2 move right after touching cube1*/
        other = (Entity *)obody->touch.data;
        slog("%s is ",other->name);
		/*Health and ammo pickup disappear when touched*/

		//other->body.velocity = vec3d(-other->body.velocity.x,-other->body.velocity.y,-other->body.velocity.z); //move cube2 in opposite direction as soon as it collides with cube1
		
    }
    slog("touching me.... touching youuuuuuuu");
}

Entity *newCube(Vec3D position, Vec3D rotation, const char *name)//creates object
{
    Entity * ent;
    ent = entity_new();
    if (!ent)
    {
        return NULL;
    }
    ent->objModel = obj_load("models/Player_Gun.obj");
    //ent->texture = LoadSprite("models/cube_text.png",1024,1024);
    vec3d_cpy(ent->body.position,position);
	ent->rotation.x = 90;
	ent->rotation.y = 180;
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newPistol(Vec3D position, Vec3D rotation)//creates object
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
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    //sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newDrone(Vec3D position, Vec3D rotation, const char *name)//creates object
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
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newTurret(Vec3D position, Vec3D rotation, const char *name)//creates object
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
    cube_set(ent->body.bounds,-1,-1,-1,2,2,2);
    sprintf(ent->name,"%s",name);
    mgl_callback_set(&ent->body.touch,touch_callback,ent);
    return ent;
}

Entity *newSoldier(Vec3D position, Vec3D rotation, const char *name)//creates object
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
	ent->rotation.x = 90;
	ent->rotation.y = 180;
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
    Entity *cube1,*pistol, *drone1, *drone2, *drone3, *drone4, *drone5, *turret1, *soldier1;
    char bGameLoopRunning = 1;
    Vec3D cameraPosition = {120,-20,0.3}; //set initial camera position
    Vec3D cameraRotation = {90,0,90};    //set initial rotation
    SDL_Event e;
    Obj *bgobj;
    Sprite *bgtext;
    
    init_logger("gametest3d.log");
    if (graphics3d_init(1024,768,1,"gametest3d",33) != 0)
    {
        return -1;
    }
    model_init();
    obj_init();
    entity_init(255);
    
    bgobj = obj_load("models/level.obj");
    bgtext = LoadSprite("models/mountain_text.png",1920,1080);
    
    cube1 = newCube(vec3d(90,-20,3),vec3d(10,5,10),"Cubert"); //create cube with position, rotation and name
	pistol = newPistol(vec3d(90,-25,1),vec3d(10,5,10));
	drone1 = newDrone(vec3d(90,-10,1),vec3d(10,5,10),"drone");
	drone2 = newDrone(vec3d(90,0,1),vec3d(10,5,10),"drone");
	drone3 = newDrone(vec3d(90,5,1),vec3d(10,5,10),"drone");
    drone4 = newDrone(vec3d(90,-30,1),vec3d(10,5,10),"drone");
	drone5 = newDrone(vec3d(90,-25,1),vec3d(10,5,10),"drone");
    turret1 = newTurret(vec3d(90,-35,1),vec3d(10,5,10),"turret");
	soldier1 = newSoldier(vec3d(90,-39,1),vec3d(10,5,10),"soldier");
    
    //cube2->body.velocity.x = -0.1; //move cube2 0.1 units left
    
    space = space_new();
    space_set_steps(space,100);
    
    space_add_body(space,&cube1->body);
	space_add_body(space,&pistol->body);
	space_add_body(space,&drone1->body);
	space_add_body(space,&drone2->body);
	space_add_body(space,&drone3->body);
	space_add_body(space,&drone4->body);
	space_add_body(space,&drone5->body);
	space_add_body(space,&turret1->body);
	space_add_body(space,&soldier1->body);
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
                }
                else if (e.key.keysym.sym == SDLK_LEFT)
                {
                    cameraRotation.z += 10;
                }
                else if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    cameraRotation.z -= 10;
                }
                else if (e.key.keysym.sym == SDLK_UP)
                {
                    cameraRotation.x += 10;
                }
                else if (e.key.keysym.sym == SDLK_DOWN)
                {
                    cameraRotation.x -= 10;
                }
            }
        }

        graphics3d_frame_begin();
        
        glPushMatrix();
        set_camera(
            cameraPosition,
            cameraRotation);
        
        entity_draw_all();  
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

