#include "model_transform.h"
#include "model.h"
#include "vertex_array.h"
#include "vertex_array_transform.h"
#include "vertex_transform.h"


static void move_center(vec3& center, const move_t& move) {
    move_vertex(center, move);
}

int move_model(model_t& model, const move_t& move) {
    vec3& center = get_center(model);
    move_center(center, move);

    return SUCCESS;
}

int rotate_model(model_t& model, const rotate_t& rotate) {
    vertex_array_t va = get_vertex_arr(model);

    return rotate_vertices(va, rotate);
}

int scale_model(model_t& model, const scale_t& scale) {
    vertex_array_t va = get_vertex_arr(model);

    return scale_vertices(va, scale);
}
