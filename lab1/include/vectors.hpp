#ifndef VECTORS_H_
#define VECTORS_H_

#include <math.h>

typedef float vec2[2];
typedef float vec3[3];
typedef int vec3i[3];
typedef float vec4[4];
typedef vec4   mat4[4];


double dotProduct3(const vec3 &a, const vec3 &b);

double dotProduct4(const vec4 &a, const vec4 &b);

void crossProduct3(const vec3 &a, const vec3 &b, vec3 &result);

void crossProduct4(const vec4 &a, const vec4 &b, vec4 &result);

void normalize3(vec3 &v);

void normarlize4(vec4 &v);

void vset(vec3 &v, float x, float y, float z);

void vadd3(const vec3 src1, const vec3 src2, vec3 &dst);

void vadd4(const vec4 src1, const vec4 src2, vec4 &dst);

void vsub(const vec3 src1, const vec3 src2, vec3&dst);

void vscale3(vec3 &v, float div);

void vscale4(vec4 &v, float div);

float vlength(vec3 v);

void vcopy3(const vec3 a, vec3 &b);

void vcopy4(const vec3 a, vec4 &b);

#endif /* VECTORS_H_ */
