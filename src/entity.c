/*create entity*/

#include "entity.h"
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
			vec3d_set(__entity_list[i].scale,1,1,1);
			__entity_list[i].destroy = 1;
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
	   // particle_draw(ent->position, ent->scale, ent->texture, 16);
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

/*void drawBB(Entity *ent)
{
	int tris[36] = 
					{1,0,2,  //create triangles
					 2,3,1,
					 5,4,0,
					 0,1,5,
					 5,1,3,
					 3,7,5,
					 6,7,2,
					 7,3,2,
					 0,4,2,
					 4,6,2,
					 4,5,6,
					 5,7,6};
	int i;
	float x = ent->body.bounds.x+ent->body.position.x; //set bounding box coordinates
	float y = ent->body.bounds.y+ent->body.position.y;
	float z = ent->body.bounds.z+ent->body.position.z;

	/*set bounding box for width,height and depth
	float w = ent->body.bounds.w;     
	float h = ent->body.bounds.h;
	float d = ent->body.bounds.d;
	Vec3D verts[8] = 
	{
		{x,y+h,z},     //get vertices
		{x+w,y+h,z},
		{x,y,z},
		{x+w,y,z},
		{x,y+h,z+d},
		{x+w,y+h,z+d},
		{x,y,z+d},
		{x+w,y,z+d}
	};
    glEnable(GL_BLEND);
    glColorMaterial(GL_FRONT,GL_DIFFUSE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	glRotatef(ent->rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(ent->rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(ent->rotation.z, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);

		for(i=0;i<12;i++)
		{
			glColor4f(1.0f,0.0f,0.0f,0.25f);  //set color
			glVertex3f(verts[tris[3*i]].x,    //get vertex coordinates
			verts[tris[3*i]].y,
			verts[tris[3*i]].z);

			glColor4f(1.0f,0.0f,0.0f,0.25f);
			glVertex3f(verts[tris[3*i+1]].x,
			verts[tris[3*i+1]].y,
			verts[tris[3*i+1]].z);

			glColor4f(1.0f,0.0f,0.0f,0.25f);
			glVertex3f(verts[tris[3*i+2]].x,
			verts[tris[3*i+2]].y,
			verts[tris[3*i+2]].z);
		}
		glEnd();
    glBegin(GL_LINES);  //begin creating lines

		for(i=0;i<12;i++)
		{
			glColor4f(1.0f,1.0f,0.0f,1.0f);
			glVertex3f(verts[tris[3*i]].x,
			verts[tris[3*i]].y,
			verts[tris[3*i]].z);

			glColor4f(1.0f,1.0f,0.0f,1.0f);
			glVertex3f(verts[tris[3*i+1]].x,
			verts[tris[3*i+1]].y,
			verts[tris[3*i+1]].z);

			glColor4f(1.0f,1.0f,0.0f,1.0f);
			glVertex3f(verts[tris[3*i+1]].x,
			verts[tris[3*i+1]].y,
			verts[tris[3*i+1]].z);

			glColor4f(1.0f,1.0f,0.0f,1.0f);
			glVertex3f(verts[tris[3*i+2]].x,
			verts[tris[3*i+2]].y,
			verts[tris[3*i+2]].z);

			glColor4f(1.0f,1.0f,0.0f,1.0f);
			glVertex3f(verts[tris[3*i+2]].x,
			verts[tris[3*i+2]].y,
			verts[tris[3*i+2]].z);

			glColor4f(1.0f,1.0f,0.0f,1.0f);
			glVertex3f(verts[tris[3*i]].x,
			verts[tris[3*i]].y,
			verts[tris[3*i]].z);
		}
		glEnd();
    
    glDisable(GL_BLEND);
    glDisable(GL_COLOR_MATERIAL);
	//slog("%s bb (%f,%f,%f,%f,%f,%f)\n",ent->name,x,y,z,ent->body.bounds.w,ent->body.bounds.h,ent->body.bounds.d);
	glPopMatrix();
}
*/
/*eol@eof*/



