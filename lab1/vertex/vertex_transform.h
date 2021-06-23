#ifndef VERTEX__TRANSFORM_
#define VERTEX__TRANSFORM_

#include "vertex.h"
#define PI 3.14159265

struct move {
    double x, y, z;
};

struct scale {
    double kx, ky, kz;
};

struct rotate {
    double ax, ay, az;
};

using move_t = struct move;
using scale_t = struct scale;
using rotate_t = struct rotate;

void move_vertex(vec3 &v, const move_t &move);
void scale_vertex(vec3 &v, const move_t &scale);
void rotate_vertex(vec3 &v, const move_t &rotate);

#endif // VERTEX__TRANSFORM_
