#ifndef MODEL__TRANSFORM_
#define MODEL__TRANSFORM_

#include "errors.h"
#include "model.h"
#include "vertex_array_transform.h"

int move_model(model_t& model, const move_t& move);
int rotate_model(model_t& model, const rotate_t& rotate);
int scale_model(model_t& model, const scale_t& scale);

#endif // MODEL__TRANSFORM_
