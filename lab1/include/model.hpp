#ifndef MODEL_H_
#define MODEL_H_

#include "GL/glew.h"
#include "vectors.hpp"
#include "errors.hpp"

typedef struct model_struct {
    vec3 *vertices;
    int vert_num;
    int *indices;
    int indices_num;
} model_t;

typedef struct {
    GLuint vbo;
    GLuint elementBuffer;
    GLuint attrib_v_coord;
    GLuint projection_matrix;
    GLuint view_matrix;
    GLuint model_matrix;
    int num;
} DrawObject;

void setVertex(model_t &model, vec3 buf);

void setFace(model_t &model, vec3i face);

int loadVertexBuffer(DrawObject &obj, 
        model_t &model, GLuint programID);

int DestroyData(model_t &model);

#endif /* MODEL_H_*/
