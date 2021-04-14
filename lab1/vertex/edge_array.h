#ifndef EDGE__ARRAY_
#define EDGE__ARRAY_

#include "edge.h"

struct face_array {
    face_t *faces;
    unsigned int n;
};

using face_array_t = struct face_array;

face_array_t face_array_init(face_t *faces = nullptr, unsigned int n = 0);
int faces_alloc(face_array_t &fa, unsigned int n);
void face_array_free(face_array_t &fa);
unsigned int face_array_len(face_array_t &fa);
face_t &get_face(face_array_t &fa, unsigned int index);

#endif // EDGE_ARRAY_
