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
#include "events.hpp"
#include "imfilebrowser.h"

typedef struct {
    GLFWwindow *window;
    camera_t cam;
    mouse_state_t mouse;
    GLuint program;
    event_t event;
    int width;
    int height;
    ImGui::FileBrowser fileDialog;
} window_t;


int startWindowContext(window_t &windowconst, int width, 
        const int height);

int runGLEW();

int initImGui(window_t &window);

void mouseMotionHandle(GLFWwindow *window, double mouseX, double mouseY);

void clickFunc(GLFWwindow *window, int button, int action, int mods);

void windowGetDimensions(window_t &window, int &width, int &height);

void setCallbacks(window_t &window);

int InitScene(window_t &window);

void runLoop(window_t &window, DrawObject &obj);

void GLFWDestroy(window_t &window);


int destroyDrawObject(window_t &window,
        DrawObject &obj);

#endif /* WINDOW_H_ */
