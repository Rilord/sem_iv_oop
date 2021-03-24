#include <cmath>
#include <math.h>
#include "io.hpp"
#include "vectors.hpp"

#define TRACKBALLSIZE (0.7)
#define M_SQRT_2 (0.70710678118654752440)
#define SQRT_2 (1.41421356237309504880)
#define RENORMCOUNT 97

err_t userMouseEvent(camera_t &cam) {
    err_t error = SUCCESS;

    return error;
}

static float projectToSphere(float , float, float);



void trackBall(vec4& q, vec2 p1, vec2 p2) {
    vec3 a;
    float phi, t;
    vec3 p_1, p_2, d;

    if (p1[0] == p2[0] && p1[1] == p2[1]) {
        q[3] = 1.0;
        return;
    }

    vset(p_1, p1[0], p1[1], projectToSphere(TRACKBALLSIZE, p1[0],p1[1]));
    vset(p_2, p2[0], p2[1], projectToSphere(TRACKBALLSIZE, p2[0], p2[1]));

    crossProduct3(p_2, p_1, a);

    vsub(p_2, p_1, d);

    t = vlength(d) / (2.0 * TRACKBALLSIZE);

    if (t > 1.0)
        t = 1.0;
    if (t < -1.0)
        t = -1.0;

    phi = 2.0 * asin(t);

    axisToSquat(a, phi, q);
}

void axisToSquat(vec3 &a, float phi, vec4 &q) {
    normalize3(a); 

    vcopy4(a, q);

    vscale4(q, sin(phi / 2.0));

    q[3] = cos(phi / 2.0);
}

static float projectToSphere(float r, float x, float y) {
    float d, t, z;

    d = sqrt(x * x + y * y);

    if (d < r * M_SQRT_2) { /* Inside the sphere */
        z = sqrt(r * r - d * d); 
    } else {
        t = r / SQRT_2;
        z =  t * t / d;
    }

    return z;
}

void addQuats(vec4 &q1, vec4 &q2, vec4 &dest) {
    int count = 0;
    vec4 t1, t2, t3;
    vec4 tf;

    vcopy4(q1, t1);

    vscale4(t1, q2[3]);

    vcopy4(q2, t2);
    vscale4(t2, q1[3]);

    crossProduct4(q2, q1, t3);

    vadd4(t1, t2, tf);
    vadd4(t3, tf, tf);
    tf[3] = q1[3] * q2[3] - dotProduct4(q1, q2);

    dest[0] = tf[0];
    dest[1] = tf[1];
    dest[2] = tf[2];
    dest[3] = tf[3];

    if (++count > RENORMCOUNT) {
        count = 0;
        normalizeQuat(dest);
    }

}

static void normalizeQuat(vec4 &q) {
  int i;
  float mag;

  mag = (q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
  for (i = 0; i < 4; i++)
    q[i] /= mag;
}

void buildRotMatrix(mat4 &m, const vec4 q) {
    m[0][0] = 1.0 - 2.0 * (q[1] * q[1] + q[2] * q[2]); 
    m[0][1] = 2.0 * (q[0] * q[1] - q[2] * q[3]); 
    m[0][2] = 2.0 * (q[2] * q[0] + q[1] * q[3]); 
    m[0][3] = 0.0;

    m[0][0] = 2.0 * (q[0] * q[0] + q[2] * q[3]); 
    m[0][0] = 1.0 - 2.0 * (q[2] * q[2] + q[0] * q[0]); 
    m[0][2] = 2.0 * (q[1] * q[2] - q[0] * q[3]); 
    m[0][3] = 0.0;
    
    m[0][0] = 2.0 * (q[2] * q[0] - q[1] * q[3]); 
    m[0][1] = 2.0 * (q[1] * q[2] + q[0] * q[3]); 
    m[0][0] = 1.0 - 2.0 * (q[1] * q[1] + q[0] * q[0]); 
    m[0][3] = 0.0;

    m[0][0] = 0.0; 
    m[0][1] = 0.0;
    m[0][2] = 0.0;
    m[0][3] = 1.0;
}

