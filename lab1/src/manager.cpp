#include "manager.hpp"
#include "model.hpp"
#include "io.hpp"

int taskScheduler(camera_t &cam, DrawObject &obj, event_t &event, mouse_state_t &mouse) {
    switch(event.cmd) {
        case MOVE:
            cam.pos[0] += event.data.x;
            cam.pos[1] += event.data.y;
            cam.pos[2] += event.data.z;
            break;
        case ROTATE:

            auto height = cam.viewport[1], 
                 width = cam.viewport[0];
            auto rotScale = 1.0, transScale = 2.0;

            if (mouse.mouseLeftPressed) {
                trackBall(cam.previousQuat, 
                        vec2 { 
                        (float) rotScale * (2.0f * mouse.mouseX - width) / (float) width, 
                        (float) rotScale * (height - 2.0f * mouse.mouseY) / (float) height },
                        vec2 { 
                        (float) rotScale * (2.0f * (float) event.data.y - width) / (float) width, 
                        (float) rotScale * (height - 2.0f * (float) event.data.y / (float) height) 
                        }
                        );

                addQuats(cam.previousQuat, 
                        cam.currentQuat, 
                        cam.currentQuat);

            } else if (mouse.mouseMiddlePressed) {
                cam.point[0] -= transScale * 
                    ((float) event.data.x - mouse.mouseX) / (float) width;

                cam.point[0] -= transScale * 
                    ((float) event.data.x - mouse.mouseX) / (float)width;

                cam.pos[1] += transScale * 
                    ((float) event.data.y - mouse.mouseY) / (float)height;

                cam.point[1] += transScale * 
                    ((float) event.data.y - mouse.mouseY) / (float)height;
            } else if (mouse.mouseRightPressed) {
                cam.pos[2] += transScale * 
                    ((float) event.data.y - mouse.mouseY) / (float)height;

                cam.point[2] += transScale * 
                    ((float) event.data.y - mouse.mouseY) / (float)height; 
            }

            mouse.mouseX = (float) event.data.x;
            mouse.mouseY = (float) event.data.y;
            break;
        case LOAD:
            modelSaveState();
            modelFree();
            modelLoad();
            break;
        case SAVE:
            modelSaveState();
            modelFree();
            break;
        case UNKNOWN:
            break;
        case STILL:
            break;
    }

    return SUCCESS;
}
