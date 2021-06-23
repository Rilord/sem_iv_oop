#ifndef VERTEX__ARRAY__TRANSFORM_
#define VERTEX__ARRAY__TRANSFORM_

#include "vertex_transform.h"
#include "vertex_array.h"
#include "errors.h"


int rotate_vertices(vertex_array_t &va, const rotate_t &rotate);

int scale_vertices(vertex_array_t &va, const scale_t &scale);

int move_vertices(vertex_array_t &va, const move_t &move);

#endif // VERTEX__ARRAY__TRANSFORM_
