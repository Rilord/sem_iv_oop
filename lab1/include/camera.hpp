#ifndef CAMERA_H_
#define CAMERA_H_

#define CAMERA_OPERATION_ERR (0x02)
#define PI 3.14159


/* Diordiev Mathematica */

typedef float vec2[2];
typedef float vec3[3];
typedef float vec3f[3];
typedef float vec4[4];
typedef vec4   mat4[4];


double dotProduct3(const vec3 &a, const vec3 &b);

double dotProduct4(const vec4 &a, const vec4 &b);

void crossProduct3(const vec3 &a, const vec3 &b, vec3 &result);

void crossProduct4(const vec4 &a, const vec4 &b, vec4 &result);

void normalize3(vec3 &v);

void normarlize4(vec4 &v);

void createMat4FromVec3(vec3 &pos, vec3 &f, vec3 &u, vec3 &r, mat4 &mat);

double rad(double angle);



/* simple camera struct */
typedef struct camera {
    vec3 pos      { 0.f, -8.f, 0.f }; /* camera position*/
    double fov    { 90.f };           /* field of view */
    vec3 point    { 0.f, 0.f, 0.f };  /* pointing to */
    vec3 up       { 0.f, 0.f, 1.f };
    vec2 viewport { 800, 600 };
    float near    { 0.5f };
    float far     { 100.f };
} camera_t;

typedef struct scene {
    camera_t cam;
    mat4 projection;
} scene_t;

void cameraGetPerspective(camera_t &cam, mat4 &perspective);

void cameraLookAt(camera_t &cam, mat4 &perspective);


#endif /* CAMERA_H_ */
