#ifndef WINDOW_H_
#define WINDOW_H_

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "errors.hpp"
#include "camera.hpp"
#include "io.hpp"
#include "model_loader.hpp"

typedef struct {
    GLFWwindow *window;
    camera_t cam;
    mouse_state_t mouse;
    GLuint program;
    int width;
    int height;
} window_t;


err_t startWindowContext(window_t &windowconst, int width, 
        const int height);

err_t runGLEW();

err_t initImGui(window_t &window);

void mouseMotionHandle(GLFWwindow *window, double mouseX, double mouseY);

void clickFunc(GLFWwindow *window, int button, int action, int mods);

void windowGetDimensions(window_t &window, int &width, int &height);

void setCallbacks(window_t &window);

err_t InitScene(window_t &window);

err_t runLoop(window_t &window, DrawObject &obj);

void GLFWDestroy(window_t &window);


err_t destroyDrawObject(window_t &window,
        DrawObject &obj);

#endif /* WINDOW_H_ */
