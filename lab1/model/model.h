#ifndef MODEL_
#define MODEL_

#include "vertex_array.h"
#include "edge_array.h"
#include "edge.h"


struct model {
    vertex_array_t va;
    face_array_t fa;

    vec3 center;
};

using model_t = struct model;

model_t model_init(vertex_array_t *va = nullptr, face_array_t *fa = nullptr);
void model_free(model_t &model);

vertex_array_t &get_vertex_arr(model_t &model);
face_array_t &get_face_arr(model_t &model);
void set_center(model_t &model, vec3 center);
vec3 &get_center(model_t &model);


#endif // MODEL_
