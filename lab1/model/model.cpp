#include "model.h"
#include "edge_array.h"
#include "vertex.h"
#include "vertex_array.h"

model_t model_init(vertex_array_t *va, face_array_t *fa) {
    model_t model;

    vertex_array_t tmp_va = { nullptr, 0 };

    if (va) {
        tmp_va.vertices = va->vertices;
        tmp_va.n = va->n;
    }

    face_array_t tmp_fa = { nullptr, 0 };

    if (fa) {
        tmp_fa.faces = fa->faces;
        tmp_fa.n = fa->n;
    }

    model.va = tmp_va;
    model.fa = tmp_fa;

    model.center = vec_init(0.0, 0.0, 0.0);

    return model;
}

void model_free(model_t &model) {
    face_array_free(model.fa);
    vertex_array_free(model.va);
}

vertex_array_t &get_vertex_arr(model_t &model) { return model.va; }
face_array_t &get_face_arr(model_t &model) { return model.fa; }
void set_center(model_t &model, vec3 center) { model.center = center; }
vec3 &get_center(model_t &model) { return model.center; }
