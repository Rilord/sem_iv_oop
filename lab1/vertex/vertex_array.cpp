#include "vertex_array.h"
#include "errors.h"

vertex_array_t vertex_array_alloc(vec3 *vertices, const unsigned int vert_num) {
    vertex_array_t va;

    va.vertices = vertices;
    va.n = vert_num;

    return va;
}

void vertex_array_free(vertex_array_t &va) {
    delete va.vertices;
    va.vertices = nullptr;
    va.n = 0;
}

int vertex_array_alloc(vertex_array_t &va, const unsigned int num) {
    va.vertices = new vec3[num];

    if (va.vertices != nullptr) {
        va.n = num;
        return SUCCESS;
    }

    return ALLOC_ERROR;
}

vec3 &get_dot(const vertex_array_t &va, int index) {
    return va.vertices[index];
}
unsigned int vertex_array_len(const vertex_array_t &va) {
    return va.n;
}

int vertex_array_is_empty(const vertex_array_t &va) {
    return va.vertices == nullptr || va.n == 0;
}
