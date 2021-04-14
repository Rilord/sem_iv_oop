#include "edge_loader.h"

#include "edge_loader.h"
#include "errors.h"
#include "vertex_loader.h"
#include "vertex_array.h"
#include "edge.h"
#include "edge_array.h"
#include "error.h"
#include <cstdio>

static int read_faces_num(FILE* file) {
    int nedges;
    int rc = fscanf(file, "%d", &nedges);

    if (rc != 1)
        return -1;

    return nedges;
}

static int read_edge(FILE* file, int* i1, int* i2, int *i3) {
    return fscanf(file, "%d %d %d", i1, i2, i3) != 2;
}

static int read_edges(FILE* file, face_array_t& edges_arr) {
    int rc = 0;
    unsigned int edges_num = face_array_len(edges_arr);

    for (unsigned int i = 0; i < edges_num && !rc; i++) {
        int i1;
        int i2;
        int i3;

        rc = read_edge(file, &i1, &i2, &i3);
        edges_arr.faces[i] = init_face(i1, i2, i3);
    }

    return rc;
}

int get_edges(face_array_t& fa, FILE* file) {
    int face_num = read_faces_num(file);

    if (face_num < 0) {
        return WRONG_FACES_NUM;
    }

    face_array_t tmp;

    if (faces_alloc(tmp, face_num) == ALLOC_ERROR) {
        return ALLOC_ERROR;
    }

    int rs = read_edges(file, tmp);

    if (rs)
        face_array_free(tmp);
    else {
        fa = tmp;
    }

    return rs;
}
