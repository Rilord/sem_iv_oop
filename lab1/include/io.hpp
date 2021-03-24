#ifndef IO_HPP_
#define IO_HPP_

#include "camera.hpp"
#include "errors.hpp"
#include "vectors.hpp"

typedef struct {
    float mouseX, mouseY;
    int mouseLeftPressed;
    int mouseRightPressed;
    int mouseMiddlePressed;
} mouse_state_t;

err_t userMouseEvent(camera_t &cam);

void trackBall(vec4& q, vec2 p1, vec2 p2);

void axisToSquat(vec3 &a, float phi, vec4 &q);

static void normalizeQuat(vec4 &q);

void buildRotMatrix(mat4 &m, const vec4 q);

void addQuats(vec4 &q1, vec4 &q2, vec4 &dest);

#endif /* IO_HPP_ */
