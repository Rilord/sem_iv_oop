#ifndef WINDOW_H_
#define WINDOW_H_

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "RenderLog.hpp"

#include "render.hpp"

#define WINDOW_SUCCESS (0x10)
#define WINDOW_GLFW_ERROR (0x11)
#define WINDOW_GLEW_ERROR (0x12)

typedef struct {
    GLFWwindow *window;
    Renderer *renderer;
} window_t;

GLFWwindow *startWindowContext();

int runGLEW();

void setCallbacks();

#endif /* WINDOW_H_ */
