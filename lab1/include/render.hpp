#ifndef RENDER_H_
#define RENDER_H_

#include "model.hpp"
#include "camera.hpp"
#include "shaders.hpp"

void drawObject(DrawObject &obj);

void setMat4(GLuint uniformLocation, const mat4 &mat);

void CheckErrors(const char* desc);


#endif /* RENDER_H_ */
