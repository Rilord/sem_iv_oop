#ifndef CAMERA_H_
#define CAMERA_H_

#include <string.h>
#include "vectors.hpp"

#define CAMERA_OPERATION_ERR (0x02)
#define PI 3.14159

void createMat4FromVec3(vec3 &pos, vec3 &f, vec3 &u, vec3 &r, mat4 &mat);

double rad(double angle);

/* simple camera struct */
typedef struct camera {
    vec3 pos      { 0.f, 0.f, 3.f }; /* camera position*/
    double fov    { 90.f };           /* field of view */
    vec3 point    { 0.f, 0.f, 0.f };  /* pointing to */
    vec3 up       { 0.f, 1.f, 0.f };
    vec2 viewport { 800, 600 };
    float near    { 0.5f };
    float far     { 100.f };
    vec4 currentQuat, previousQuat;
} camera_t;

void cameraGetPerspective(camera_t &cam, mat4 &perspective);

void cameraLookAt(camera_t &cam, mat4 &perspective);

void modelMatrix(mat4 &mat);


#endif /* CAMERA_H_ */
