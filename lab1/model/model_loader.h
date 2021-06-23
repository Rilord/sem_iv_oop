#ifndef MODEL__LOADER_
#define MODEL__LOADER_

#include "model.h"
#include "my_string.h"
#include <stdio.h>

int scan_model(model_t &model, FILE *file);
int scan_file(model_t &model, const char *filename);
int save_to_file(const model_t& model, const char* filename);

#endif // MODEL__LOADER_
