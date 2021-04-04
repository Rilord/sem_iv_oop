#include "window.hpp"
#include "GLFW/glfw3.h"
#include "camera.hpp"
#include "imgui.h"
#include "manager.hpp"
#include "model.hpp"
#include "render.hpp"
#include "io.hpp"
#include "imfilebrowser.h"
#include <string.h>

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    window_t *win = (window_t *) glfwGetWindowUserPointer(window);

    switch(key) {
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, 
                        GLFW_TRUE);
            }
                break;
        case GLFW_KEY_K:
            win->event.cmd = MOVE;
            win->event.data.x = 1;
            win->event.data.y = 0;
            win->event.data.z = 0;
            break;
        case GLFW_KEY_J:
            win->event.cmd = MOVE;
            win->event.data.x = -1;
            win->event.data.y = 0;
            win->event.data.z = 0;
            break;
        case GLFW_KEY_L:
            win->event.cmd = MOVE;
            win->event.data.x = 0;
            win->event.data.y = 1;
            win->event.data.z = 0;
            break;
        case GLFW_KEY_H:
            win->event.cmd = MOVE;
            win->event.data.x = 0;
            win->event.data.y = -1;
            win->event.data.z = 0;
            break;
        default:
            break;
    }
}

int startWindowContext(window_t &window, const int width, const int height) {

    if (!glfwInit()) {
        return WINDOW_ERR;
    }

    window.window = glfwCreateWindow(width, height, "oop", NULL, NULL);

    if (!window.window) {
        glfwTerminate();
        return WINDOW_ERR;
    }

    glfwSetWindowUserPointer(window.window, &window);

    glfwMakeContextCurrent(window.window);

    return SUCCESS;
}

int runGLEW() {
    if (glewInit() != GLEW_OK) {
        return WINDOW_ERR;
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

void runLoop(window_t &window, renderer &r) {
    auto rc = 0;
    std::string selectedFile;
    while (!glfwWindowShouldClose(window.window)) {

        glfwPollEvents();


        glEnable(GL_DEPTH_TEST);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        if (ImGui::Button("Open")) {
            window.event.cmd = LOAD;
        }

        if (ImGui::Button("Save")) {
            
        }

        if (ImGui::Button("Exit")) {
            
        }


        ImGui::NewFrame();

        ImGui::Begin("Lab");
        
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open..", "Ctrl+O"))
                {
                    window.fileDialog.Open();

                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        ImGui::End();

        window.fileDialog.Display();

        if(window.fileDialog.HasSelected())
        {
            selectedFile = window.fileDialog.GetSelected();
            window.fileDialog.ClearSelected();
        }
        ImGui::Render();


        glClearColor(0.3f, 0.5f, 0.6f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwPollEvents();

        if (window.event.cmd != STILL)
            int rc = taskScheduler(window.cam, r.obj, window.event);

        if (rc) {
            ErrorHandler(rc);
        }

        r.render(r.obj, window.cam, window.program);

        glfwSwapBuffers(window.window);

    }

}

void setCallbacks(window_t &window) {
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window.window, key_callback);
    glfwSetCursorPosCallback(window.window, mouseMotionHandle);
}

void clickFunc(GLFWwindow *window, int button, int action, int mod) {

    window_t *window_context = (window_t *) glfwGetWindowUserPointer(window);

    switch(button) {
        case GLFW_MOUSE_BUTTON_LEFT:
            if (action == GLFW_PRESS)
                window_context->mouse.mouseLeftPressed = 1;
            else if (action == GLFW_RELEASE)
                window_context->mouse.mouseLeftPressed = 0;
            break;
        case GLFW_MOUSE_BUTTON_RIGHT:
            if (action == GLFW_PRESS)
                window_context->mouse.mouseRightPressed = 1;
            else if (action == GLFW_RELEASE)
                window_context->mouse.mouseRightPressed = 0;
            break;
        case GLFW_MOUSE_BUTTON_MIDDLE:
            if (action == GLFW_PRESS)
                window_context->mouse.mouseMiddlePressed = 1;
            else if (action == GLFW_RELEASE)
                window_context->mouse.mouseMiddlePressed = 0;
            break;
        default:
            break;
    }
     
}

void mouseMotionHandle(GLFWwindow *window, double mouseX, double mouseY) {
    int width, height;

    window_t *win = (window_t *) glfwGetWindowUserPointer(window);

    windowGetDimensions(*win, width, height);
    
}

void windowGetDimensions(window_t &window, int &width, int &height) {
    width = window.width;
    height = window.height;

}

int destroyDrawObject(window_t &window, 
        DrawObject &obj) {
    auto error = SUCCESS;

    GLFWDestroy(window);

    glDeleteProgram(window.program); 

    glDeleteBuffers(1, &obj.vbo);

    return error;
}

int InitScene(window_t &window) {
    auto error = SUCCESS;

    window.program = glCreateProgram();

    return error;
}

void GLFWDestroy(window_t &window) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window.window);
    glfwTerminate();
    
}
