#include "window.hpp"
#include "GLFW/glfw3.h"
#include "RenderLog.hpp"
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

GLFWwindow *startWindowContext(const int width, const int height) {
    if (!glfwInit()) {
        RenderError("couldn't init GLFW context");
        return NULL;
    }

    RenderProceed("Successfully inited GLFW context");

    return NULL;

    GLFWwindow *window = glfwCreateWindow(width, height, "oop", NULL, NULL);

    if (!window) {
        RenderError("couldn't create GLFW window");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    return window;
}

int runGLEW() {
    if (glfwInit() != GLEW_OK) {
        RenderError("couldn't create GLEW context");
        return WINDOW_GLEW_ERROR;
    }
    RenderProceed("GLEW was initialized");

    return WINDOW_SUCCESS;
}

int initimgui(window_t &window) {

#ifdef __APPLE__
    const char *glsl_version = "#version 150";
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

    return WINDOW_SUCCESS;

}

void runLoop(window_t &window) {
    while (!glfwWindowShouldClose(window.window)) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        ImGui::Begin("menu");

        ImGui::Render();

        glClearColor(0.3f, 0.5f, 0.6f, 1.f);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window.window);

        glfwPollEvents();
    }
    
}


void setCallbacks(window_t &window) {
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window.window, key_callback);
}

