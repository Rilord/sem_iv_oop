#include "vertex_array_transform.h"
#include "errors.h"
#include "vertex_array.h"
#include "vertex_transform.h"

int rotate_va(vertex_array_t& va, const rotate_t& rotate) {
    if (vertex_array_is_empty(va))
        return ROTATION_ERROR;

    unsigned int nva = vertex_array_len(va);

    for (unsigned int i = 0; i < nva; i++) {
        vec3& v = get_dot(va, i);
        rotate_vertex(v, rotate);
    }

    return SUCCESS;
}

int scale_va(vertex_array_t& va, const scale_t& scale) {
    if (vertex_array_is_empty(va))
        return SCALING_ERROR;

    unsigned int nva = vertex_array_len(va);

    for (unsigned int i = 0; i < nva; i++) {
        vec3& v = get_dot(va, i);
        scale_vertex(v, scale);
    }

    return SUCCESS;
}

int move_va(vertex_array_t& va, const move_t& move) {
    if (vertex_array_is_empty(va))
        return MOVE_ERROR;

    unsigned int nva = vertex_array_len(va);

    for (unsigned int i = 0; i < nva; i++) {
        vec3& dot = get_dot(va, i);
        move_dot(dot, move);
    }

    return SUCCESS;
}
