#ifndef MODEL_LOADER_H_
#define MODEL_LOADER_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "errors.hpp"
#include "camera.hpp"
#include "model.hpp"

#define VALUES_OFFSET 2

typedef struct string_struct {
    char *str;
    size_t len;
} string;

static err_t parseLine(model_t &model, string &p);

static err_t parseFloat3(vec3 &vertex, string &str);

static err_t parseInt3(vec3i &vertex, string &str);

err_t parseVertexFile(model_t &model, string &file);

static err_t prepareData(model_t &model, FILE *f);


#endif /* MODEL_LOADER_H_ */

