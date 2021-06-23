#include "edge_loader.h"
#include "edge.h"
#include "edge_array.h"
#include "errors.h"

static int read_faces_num(FILE* file) {
    int nfaces;
    int rc = fscanf(file, "%d", &nfaces);

    if (rc != 1)
        return -1;

    return nfaces;
}

static int read_face(FILE* file, int* i1, int* i2, int *i3) {
    return fscanf(file, "%d %d %d", i1, i2, i3) != 2;
}

static int read_faces(FILE* file, face_array_t& fa) {
    int rc = 0;
    unsigned int faces_num = face_array_len(fa);

    for (unsigned int i = 0; i < faces_num && !rc; i++) {
        int i1;
        int i2;
        int i3;

        rc = read_face(file, &i1, &i2, &i3);
        fa.faces[i] = init_face(i1, i2, i3);
    }

    return rc;
}

int get_faces(face_array_t& faces_arr, FILE* file) {
    int face_num = read_faces_num(file);

    if (face_num < 0) {
        return WRONG_FACES_NUM;
    }

    face_array_t tmp_faces;

    if (faces_alloc(tmp_faces, face_num) == ALLOC_ERROR) {
        return ALLOC_ERROR;
    }

    int rs = read_faces(file, tmp_faces);

    if (rs)
        face_array_free(tmp_faces);
    else {
        faces_arr = tmp_faces;
    }

    return rs;
}
