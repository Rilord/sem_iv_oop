#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "imfilebrowser.h"
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
 
    /* GLFW */

    if (!glfwInit())
    { 
        std::cout << "[FAIL] can't init glfw.\n";
        return -1;
    }
    else
    {
        std::cout << "[SUCCESS] glfw was inited.\n";
    }
#ifdef __APPLE__
    const char *glsl_version = "#version 150";
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    float highDPIscaleFactor = 1.0;
#endif

#ifdef __linux__
    const char *glsl_version = "#version 150";
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    float highDPIscaleFactor = 1.0;
#endif

    GLFWwindow* window;

    window = glfwCreateWindow(800, 600, "lab1", NULL, NULL);


    if (!window)
    {
        std::cout << "[FAIL] can't create window.\n";
        glfwTerminate();
        return -1;
    }

    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    /* GLFW */

    /* =================== */
    /* GLEW */
    if(GLEW_OK != glewInit()) 
    {
        std::cout << "[FAIL] can't init glew.\n";
        return -1;
    }
    else
    {
        std::cout << "[SUCCESS] glew was initialized.\n";
    }
    /* GLEW */

    /* IMGUI */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    io.Fonts->AddFontDefault();
    ImVec4 clear_color = ImVec4(0.3f, 0.55f, 0.60f, 1.00f);


    ImGui::FileBrowser fileDialog;

    /* IMGUI */

    /* IMPLOT */
    ImPlot::CreateContext();
    /* IMPLOT */


    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();


        ImGui::NewFrame();

        ImGui::Begin("Lab");

        ImGui::Render();


        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);


        glfwPollEvents();
    }

    glDisableVertexAttribArray(0);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
