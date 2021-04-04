#ifndef SHADERS_H_
#define SHADERS_H_

#include <stdlib.h>
#include <stdio.h>
#include "GL/glew.h"
#include "errors.hpp"
#include "vectors.hpp"

void CheckErrors(const char* desc);

int LoadShader(GLuint program);

void setMat4(GLuint program, const char *name, const mat4 &mat);

#endif /* SHADERS_H_ */
