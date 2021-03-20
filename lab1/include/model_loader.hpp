#ifndef MODEL_LOADER_H_
#define MODEL_LOADER_H_

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "errors.hpp"
#include "parse_funcs.hpp"
#include "camera.hpp"
#include "model.hpp"

typedef struct model_file_struct {
    char *filename;
    size_t len;
} model_file;

typedef struct parsing_buffer_struct {
    float v[3];
} parsing_buffer;

typedef struct string_struct {
    char *str;
    size_t len;
} string;


static err_t parseLine(string &str);

static err_t parseFloat3(vec3 &vertex, string &str);

err_t parseVertexFile(model_file &model_data, model_t &model);

static size_t getVerticesNum(FILE *f);

#endif /* MODEL_LOADER_H_ */

