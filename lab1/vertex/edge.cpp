#include "edge.h"

face_t init_face(const unsigned int i1, const unsigned int i2, const unsigned int i3) {
    face_t face;

    face.i1 = i1;
    face.i2 = i2;
    face.i3 = i3;

    return face;
}
