#ifndef VERTEX_
#define VERTEX_

#include "errors.h"

typedef struct vertex {
    double x, y, z; 
} vec3;

vec3 vec_init(const double x, const double y, const double z);
void vec_free(const vec3 *vert);

#endif // VERTEX_
