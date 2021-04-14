#include "edge_array.h"

face_array_t face_array_init(face_t *faces, unsigned int n) {
    face_array_t fa;

    fa.faces = faces;
    fa.n = n;

    return fa;
}

int faces_alloc(face_array_t &fa, unsigned int n) {
    fa.faces = new face_t[n];

    if (fa.faces != nullptr) {
        fa.n = n;
        return SUCCESS;
    }

    return ALLOC_ERROR;
}

void face_array_free(face_array_t &fa) {
    delete fa.faces;
    fa.faces = nullptr;
    fa.n = 0;
}

unsigned int face_array_len(face_array_t &fa) {
    return fa.n;
}
face_t &get_face(face_array_t &fa, unsigned int index) {
    return fa.faces[index];
}


