#ifndef VERTEX__ARRAY_
#define VERTEX__ARRAY_

#include "vertex.h"

struct vertex_array {
    vec3 *vertices;
    unsigned int n;
};

using vertex_array_t = struct vertex_array;

vertex_array_t vertex_array_init(vertex_array_t *va = nullptr, const unsigned int vert_num = 0);

int vertex_array_alloc(vertex_array_t &va, const unsigned int num);

void vertex_array_free(vertex_array_t &va);

vec3 &get_dot(const vertex_array_t &va, int index);

unsigned int vertex_array_len(const vertex_array_t &va);

int vertex_array_is_empty(const vertex_array_t &va);

#endif // VERTEX__ARRAY_
