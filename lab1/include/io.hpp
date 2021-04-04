#ifndef IO_HPP_
#define IO_HPP_

#include "camera.hpp"
#include "errors.hpp"
#include "vectors.hpp"
#include "events.hpp"

typedef struct {
    float mouseX, mouseY;
    int mouseLeftPressed;
    int mouseRightPressed;
    int mouseMiddlePressed;
} mouse_state_t;

int userMouseEvent(camera_t &cam);

void trackBall(vec4& q, vec2 p1, vec2 p2);

void axisToSquat(vec3 &a, float phi, vec4 &q);

static void normalizeQuat(vec4 &q);

void buildRotMatrix(mat4 &m, const vec4 q);

void addQuats(vec4 &q1, vec4 &q2, vec4 &dest);

void rotateModel(camera_t &cam, mouse_state_t &mouse, event_t &event) {

    float rotScale = 1.0f;
    float transScale = 2.0f;
    trackBall(cam.previousQuat, 
            vec2 { 
            rotScale * (2.0f * mouse.mouseX - cam.viewport[0]) / (float) cam.viewport[0], 
            rotScale * (cam.viewport[1] - 2.0f * mouse.mouseY) / (float) cam.viewport[1] },
            vec2 { 
            rotScale * (2.0f * (float) event.data.x - cam.viewport[0]) / (float) cam.viewport[0], 
            rotScale * (cam.viewport[1] - 2.0f * (float) event.data.y / (float) cam.viewport[1]) 
            }

}

#endif /* IO_HPP_ */
