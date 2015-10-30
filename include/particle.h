#ifndef _PARTICLE_h
#define PARTICLE_h

Vec2D smokeFrame(int frameNum);
Sprite *texture; 
void particle_draw(Vec3D position, Vec3D scale, Sprite *texture, int frameNum);

#endif