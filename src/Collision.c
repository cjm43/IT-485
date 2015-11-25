#include "Collision.h"
#include "math.h"
#include "simple_logger.h"

int sphere_sphere_intersection(
    Vec3D c1,float r1,   /*sphere 1*/
    Vec3D c2,float r2    /*sphere 2*/
)
{
    float distance;
    distance = 
    (c1.x - c2.x)*(c1.x - c2.x) +
    (c1.y - c2.y)*(c1.y - c2.y) +
    (c1.z - c2.z)*(c1.z - c2.z);
    if (distance <= ((r1 + r2) * (r1 + r2)))
    {
        return 1;
    }
    return 0;
}

int point_cube_intersection(
    Vec3D point,            /*point*/
    Vec3D box, Vec3D size)  /*cube*/
{
    if ((point.x < box.x) ||
        (point.y < box.y) ||
        (point.z < box.z) ||
        (point.x > box.x + size.x) ||
        (point.y > box.y + size.y) ||
        (point.z > box.z + size.z))
    {
        return 0;
    }
    return 1;
}

int sphere_cube_intersection(
    Vec3D center,float r,   /*sphere*/
    Vec3D box, Vec3D size)  /*axis aligned 3d cube*/
{
    float distance;
    Vec3D offset;
    
    offset.x = -(box.x + (size.x * 0.5));
    offset.y = -(box.y + (size.y * 0.5));
    offset.z = -(box.z + (size.z * 0.5));
    
    vec3d_add(box,box,offset);
    vec3d_add(center,center,offset);
    center.x = fabs(center.x);
    center.y = fabs(center.y);
    center.z = fabs(center.z);
    box.x = fabs(box.x);
    box.y = fabs(box.y);
    box.z = fabs(box.z);
    
    distance = 
        (box.x - center.x)*(box.x - center.x) +
        (box.y - center.y)*(box.y - center.y) +
        (box.z - center.z)*(box.z - center.z);
    
    if (distance <= (r * r))
    {
        /*success, intersection with corner*/
        return 1;
    }
    
    if ((center.x <= box.x + r) &&
        (center.y <= box.y) &&
        (center.z <= box.z))
    {
        return 1;
    }
    if ((center.x <= box.x) &&
        (center.y <= box.y + r) &&
        (center.z <= box.z))
    {
        return 1;
    }
    if ((center.x <= box.x) &&
        (center.y <= box.y) &&
        (center.z <= box.z + r))
    {
        return 1;
    }
    return 0;
}

int cube_cube_intersection(
    Cube a,
    Cube b)
{
    //if ((a.x > b.x + b.w) || (b.x > a.x + a.w) || //if length of a.x is greater than length of b.x plus the width of b
    //    (a.y > b.y + b.h) || (b.y > a.y + a.h) ||
    //    (a.z > b.z + b.d) || (b.z > a.z + a.d))
    //{
    //    return 0;  //no intersection
    //}
    //return 1; //intersection

	 return (a.x+a.w >= b.x && a.x <= b.x+b.w) //if the x value plus width of a is greater than or equal to x value of b and x value of a is less than or equal to x value plus the width of b
     && (a.y+a.h >= b.y && a.y <= b.y+b.h) //if y value plus height of a is greater than or equal to y value of b and y value of a is less than or equal to the y value plus the height of b
     && (a.z+a.d >= b.z && a.z <= b.z+b.d); //if z value plus depth of a is greater than or equal to z value of b and z value of a is less than or equal to the z value plus the depth of b
}

/*eol@eof*/