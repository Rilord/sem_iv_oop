#include "vertex_loader.h"
#include "errors.h"
#include "vertex_array.h"

static int get_vert_num(FILE *file) {
    int n;
    int rc = fscanf(file, "%d", &n);

    if (rc != 1) 
        return -1;

    return n;
}

static int read_vertex(vec3 &v, FILE *file) {
    return fscanf(file, "%lf %lf %lf", &v.x, &v.y, &v.z) != 3; 
}

static int read_vertices(vertex_array_t &va, FILE *file) {
    int rc = 0;

    unsigned int vert_num = get_vert_num(file);

    for (unsigned int i = 0; i < vert_num && !rc; i++) {
        vec3 &v = get_dot(va, i);
        rc = read_vertex(v, file);
    }

    return rc;
}

int scan_vertices(vertex_array_t &va, FILE *file) {
    auto vert_num = get_vert_num(file);

    if (vert_num == -1) {
        return WRONG_VERTICES_NUM; 
    }

    vertex_array_t tmp;

    if (vertex_array_alloc(tmp, vert_num)) {
        return ALLOC_ERROR;
    }

    int rc = read_vertices(tmp, file);

    if (rc) 
        vertex_array_free(tmp);
    else {
        va = tmp;
    }

    return rc;
}
