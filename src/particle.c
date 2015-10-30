#include "vector.h" 
#include "sprite.h"
#include "particle.h" 
#include "obj.h"

Vec2D smokeFrame(int frameNum)
{
	Vec2D pos;
	pos.x = 64*(frameNum%8);
	pos.y = (frameNum/8)*64;
	return pos;
}

void particle_draw(Vec3D position, Vec3D scale, Sprite *texture, int frameNum)
{ 
	int x,y;

	Vec2D frame = smokeFrame(frameNum);

    Vec2D obj_rect[]={{position.x,position.y},
		            {position.x + 64,position.y},
					{position.x,position.y + 64},
	                {position.x + 64,position.y + 64}};


	Vec2D uv_rect[]={{frame.x , frame.y},
		          {frame.x  + 64 , frame.y},
			      {frame.x  , frame.y + 64,},
	              {frame.x  + 64 , frame.y + 64}};

	glPushMatrix();

    glEnable(GL_BLEND);
    glColorMaterial(GL_FRONT,GL_DIFFUSE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    if(texture != NULL)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,texture->texture);
    }
	else
		return;

	glEnable(GL_COLOR_MATERIAL);
   
    glDepthFunc(GL_LEQUAL);
    
    glTranslatef(position.x,position.y,position.z);
    glScalef(scale.x,scale.y,scale.z);
    
 
    glBegin(GL_TRIANGLES);

		/*glVertex2d(obj_rect[3].x,obj_rect[3].y);
        glTexCoord2d(uv_rect[3].x,uv_rect[3].y);

		glVertex2d(obj_rect[1].x,obj_rect[1].y);
        glTexCoord2d(uv_rect[1].x,uv_rect[1].y);

		glVertex2d(obj_rect[0].x,obj_rect[0].y);
        glTexCoord2d(uv_rect[0].x,uv_rect[0].y);

		glVertex2d(obj_rect[0].x,obj_rect[0].y);
        glTexCoord2d(uv_rect[0].x,uv_rect[0].y);

		glVertex2d(obj_rect[2].x,obj_rect[2].y);
        glTexCoord2d(uv_rect[2].x,uv_rect[2].y);

		glVertex2d(obj_rect[3].x,obj_rect[3].y);
        glTexCoord2d(uv_rect[3].x,uv_rect[3].y);*/

		glTexCoord2d(1,0); glVertex2f(x+0.5f,y-0.5f);
		glTexCoord2d(0,1); glVertex2f(x+0.5f,y-0.5f);
		glTexCoord2d(1,1); glVertex2f(x+0.5f,y-0.5f);
		glTexCoord2d(0,0); glVertex2f(x+0.5f,y-0.5f);

	glEnd();
    
    glColor4f(1,1,1,1);
   
    glDisable(GL_BLEND);
    glDisable(GL_COLOR_MATERIAL);
    if(texture != NULL)
    {
        glDisable(GL_TEXTURE_2D);
    }    
          
 
    glPopMatrix();
}