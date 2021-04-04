#include "camera.hpp"
#include "io.hpp"

#include <cstdio>
#include <math.h>


double rad(double angle) {
    return angle * PI / 180.f;
}

void createMat4FromVec3(vec3 &pos, vec3 &f, vec3 &u, vec3 &r, mat4 &mat) {
    mat[0][0] = u[0]; mat[0][1] = r[0]; mat[0][2] = f[0]; mat[0][3] = 0.f;

    mat[1][0] = u[1]; mat[1][1] = r[1]; mat[1][2] = f[1]; mat[1][3] = 0.f;

    mat[2][0] = u[2]; mat[2][1] = r[2]; mat[2][2] = f[2]; mat[2][3] = 0.f;

    mat[3][0] = dotProduct3(u, pos); 
    mat[3][1] = dotProduct3(r, pos); 
    mat[3][2] = dotProduct3(vec3 { -f[0], -f[1], -f[2] }, pos);
    mat[3][3] = 1.f;
}

void cameraLookAt(camera_t &cam, mat4 &perspective) {
    vec3 forward = { 
        cam.pos[0] - cam.point[0], 
        cam.pos[1] - cam.point[1], 
        cam.pos[2] - cam.point[2] 
    };

    normalize3(forward);

    vec3 right = { cam.up[0], cam.up[1], cam.up[2] };

    vec3 up;
    crossProduct3(right, forward, up);

    normalize3(up);

    crossProduct3(forward, up, right);

    createMat4FromVec3(cam.pos, forward, up, right, perspective);

}

void cameraGetPerspective(camera_t &cam, mat4 &perspective) {

    float fn = cam.far + cam.near;

    float f_n = cam.far - cam.near;

    double r = (double) cam.viewport[0] / cam.viewport[1];

    double t = 1.f / tan(rad(cam.fov) / 2.f );

    perspective[0][0] = t / r;
    perspective[0][1] = 0.f;
    perspective[0][2] = 0.f;
    perspective[0][3] = 0.f;

    perspective[0][0] = 0.f;
    perspective[0][1] = t;
    perspective[0][2] = 0.f;
    perspective[0][3] = 0.f;

    perspective[0][0] = 0.f;
    perspective[0][1] = 0.f;
    perspective[0][2] = -fn / f_n;
    perspective[0][3] = -1.f;

    perspective[0][0] = 0.f;
    perspective[0][1] = 0.f;
    perspective[0][2] = -2.f * cam.far * cam.near / f_n;
    perspective[0][3] = 0.f;
}

void modelMatrix(mat4 &mat) {

    mat[0][0] = 1;
    mat[1][1] = 1;
    mat[2][2] = 1;
    mat[3][3] = 1;
}

void saveModelState(FILE *f, camera_t &cam) {
    fprintf(f, "%f %f %f\n", cam.pos[0], cam.pos[1], cam.pos[2]);
    fprintf(f, "%f %f %f\n", cam.point[0], cam.point[1], cam.point[2]);
    fclose(f);
    
}

void loadModelState(camera_t &cam, FILE *f) {
    fscanf(f, "%f %f %f\n", &cam.pos[0], 
            &cam.pos[1], &cam.pos[2]);
    fscanf(f, "%f %f %f\n", &cam.point[0], 
            &cam.point[1], &cam.point[2]);
    fclose(f); 
}
