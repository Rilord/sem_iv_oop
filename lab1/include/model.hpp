#ifndef MODEL_H_
#define MODEL_H_

#include "GL/glew.h"

typedef struct model_struct {
    float *VAO;
    int num;
    GLuint vbo;
} model_t;

#endif /* MODEL_H_*/
