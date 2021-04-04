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

static int parseLine(model_t &model, string &p);

static int parseFloat3(vec3 &vertex, string &str);

static int parseInt3(vec3i &vertex, string &str);

int parseVertexFile(model_t &model, string &file);

static int prepareData(model_t &model, FILE *f);

int loadModel(string &str);


#endif /* MODEL_LOADER_H_ */

