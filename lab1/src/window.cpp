#include "render.hpp"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int startWindowContext(const int width, const int height, window_t &window) {

    if (!glfwInit()) {
        return -1;
    }

    window.window = glfwCreateWindow(width, height, "oop", NULL, NULL);

    if (!window.window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window.window);

    return SUCCESS;
}

int runGLEW() {
    if (glewInit() != GLEW_OK) {
        return WINDOW_GLEW_ERROR;
    }

    return SUCCESS;
}

int initImGui(window_t &window) {

#ifdef __APPLE__
    const char *glsl_version = "#version 110";
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

#ifdef __linux__
    const char *glsl_version = "#version 330";
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
#endif

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;

    ImGui_ImplGlfw_InitForOpenGL(window.window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    io.Fonts->AddFontDefault();

    return SUCCESS;
}

void runLoop(window_t &window) {
    while (!glfwWindowShouldClose(window.window)) {

        glfwPollEvents();

        glClearColor(0.3f, 0.5f, 0.6f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);

        window.draw(window);

        glfwSwapBuffers(window.window);

    }
    
}

void setCallbacks(window_t &window) {
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window.window, key_callback);
}

