#include "vectors.hpp"

double dotProduct3(const vec3 &a, const vec3 &b) {

    return a[0] * b[0] + a[1] * b[1]  + a[2] * b[2];
}

void crossProduct3(const vec3 &a, const vec3 &b, vec3 &result) {

    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize3(vec3 &v) {
    double len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    v[0] /= len; v[1] /= len; v[2] /= len;
}


void normalize4(vec4 &v) {
    double len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
    v[0] /= len; v[1] /= len; v[2] /= len; v[3] /= len;
}

void vset(vec3 &v, float x, float y, float z) {
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

void vadd3(const float *src1, const float *src2, vec3 &dst) {
    dst[0] = src1[0] + src2[0];
    dst[1] = src1[1] + src2[1];
    dst[2] = src1[2] + src2[2];
}

void vsub(const float *src1, const float *src2, vec3 &dst) {
    dst[0] = src1[0] - src2[0];
    dst[1] = src1[1] - src2[1];
    dst[2] = src1[2] - src2[2];
}

float vlength(vec3 v) {
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]); 
}

void vscale3(vec3 &v, float div) {
    v[0] *= div;
    v[1] *= div;
    v[2] *= div;
}

void vscale4(vec4 &v, float div) {
    v[0] *= div;
    v[1] *= div;
    v[2] *= div;
}

void vcopy3(const vec3 a, vec3 &b) {
    for (auto i = 0; i  < 3; i++) {
        b[i] = a[i];
    }
}

void vcopy4(const vec3 a, vec4 &b) {
    for (auto i = 0; i  < 3; i++) {
        b[i] = a[i];
    }
}
