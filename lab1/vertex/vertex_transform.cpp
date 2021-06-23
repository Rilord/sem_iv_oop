#include "vertex_transform.h"
#include <cmath>

static inline double to_rad(double angle) { return angle * (PI / 180.0); }

static void rotate_x(vec3 &vec, const double angle) {
    double rad = to_rad(angle);

    double tmp_y = vec.y;

    vec.y = vec.y * cos(rad) + vec.z * sin(rad);
    vec.z = -tmp_y * sin(rad) + vec.z * cos(rad);
}

static void rotate_z(vec3 &vec, const double angle) {
    double rad = to_rad(angle);

    double tmp_x = vec.x;

    vec.x = vec.x * cos(rad) - vec.y * sin(rad);
    vec.y = tmp_x * sin(rad) + vec.y * cos(rad);
}

static void rotate_y(vec3 &vec, const double angle) {
    double rad = to_rad(angle);

    double tmp_x = vec.x;

    vec.x = vec.x * cos(rad) + vec.z * sin(rad);
    vec.z = -tmp_x * sin(rad) + vec.z * cos(rad);
}

void move_vertex(vec3 &v, const move_t &move) {
    v.x += move.x;
    v.y += move.y;
    v.z += move.z;
}

void scale_vertex(vec3 &v, const scale_t &k) {
    v.x *= k.kx;
    v.y *= k.ky;
    v.z *= k.kz;
}
void rotate_vertex(vec3& v, const rotate_t& rotate) {
    rotate_x(v, rotate.ax);
    rotate_y(v, rotate.ay);
    rotate_z(v, rotate.az);
}
