#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "imfilebrowser.h"
#include "render.hpp"
#include <iostream>
#include <string>

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(int argc, char *argv[])
{
    window_t MainWindow;

    if (startWindowContext(800, 600, MainWindow))
    {
        printf("Couldn't init GLFW\n");
        return 1;
    }

    setCallbacks(MainWindow);

    if (runGLEW()) {
        printf("Couldn't init GLEW");
        return 1;
    }

    if (initImGui(MainWindow)) {
        printf("Couldn't init ImGUI");
        return 1;
    }

    if (InitScene(MainWindow)) {
        printf("Couldn't init scene");
        return 1;
    }

    printf("%d - triangles\n", MainWindow.model.num);

    runLoop(MainWindow);


    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(MainWindow.window);
    glfwTerminate();
    return 0;
}
