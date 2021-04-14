#ifndef FACE_
#define FACE_

#include "vertex.h"
#include "errors.h"

struct face {
    unsigned int i1, i2, i3;
};

using face_t = struct face;

face_t init_face(const unsigned int i1, const unsigned int i2, const unsigned int i3); 

#endif // FACE_
