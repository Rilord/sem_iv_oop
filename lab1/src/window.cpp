#include "window.hpp"
#include "GLFW/glfw3.h"
#include "camera.hpp"
#include "model.hpp"
#include "render.hpp"
#include "io.hpp"

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
             win->cam.pos[0] += 1;
            break;
        case GLFW_KEY_J:
             win->cam.pos[0] -= 1;
            break;
        case GLFW_KEY_L:
             win->cam.pos[1] += 1;
            break;
        case GLFW_KEY_H:
             win->cam.pos[1] -= 1;
            break;
        default:
            break;
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

err_t startWindowContext(window_t &window, const int width, const int height) {

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

err_t runGLEW() {
    if (glewInit() != GLEW_OK) {
        return WINDOW_ERR;
    }

    return SUCCESS;
}

err_t initImGui(window_t &window) {

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

err_t runLoop(window_t &window, DrawObject &obj) {
    auto error = SUCCESS;
    while (!glfwWindowShouldClose(window.window)) {

        glfwPollEvents();

        glClearColor(0.3f, 0.5f, 0.6f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);

        drawObject(obj);

        glfwSwapBuffers(window.window);

    }

    return error; 
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
    float rotScale = 1.0f;
    float transScale = 2.0f;
    int width, height;

    window_t *win = (window_t *) glfwGetWindowUserPointer(window);

    windowGetDimensions(*win, width, height);

    

    if (win->mouse.mouseLeftPressed) {
        trackBall(win->cam.previousQuat, 
                vec2 { 
                rotScale * (2.0f * win->mouse.mouseX - width) / (float) width, 
                rotScale * (height - 2.0f * win->mouse.mouseY) / (float) height },
                vec2 { 
                rotScale * (2.0f * (float) mouseX - width) / (float) width, 
                rotScale * (height - 2.0f * (float) mouseY / (float) height) 
                }
                );

        addQuats(win->cam.previousQuat, 
                win->cam.currentQuat, 
                win->cam.currentQuat);
        
    } else if (win->mouse.mouseMiddlePressed) {
             win->cam.point[0] -= transScale * 
                 ((float)mouseX - win->mouse.mouseX) / (float) width;

            win->cam.point[0] -= transScale * 
                ((float) mouseX - win->mouse.mouseX) / (float)width;

            win->cam.pos[1] += transScale * 
                ((float) mouseY - win->mouse.mouseY) / (float)height;

            win->cam.point[1] += transScale * 
                ((float) mouseY - win->mouse.mouseY) / (float)height;

    } else if (win->mouse.mouseRightPressed) {
            win->cam.pos[2] += transScale * 
              ((float) mouseY - win->mouse.mouseY) / (float)height;

            win->cam.point[2] += transScale * 
                ((float) mouseY - win->mouse.mouseY) / (float)height; 
    }

    win->mouse.mouseX = (float) mouseX;
    win->mouse.mouseY = (float) mouseY;

    
}

void windowGetDimensions(window_t &window, int &width, int &height) {
    width = window.width;
    height = window.height;

}

err_t destroyDrawObject(window_t &window, 
        DrawObject &obj) {
    auto error = SUCCESS;

    GLFWDestroy(window);

    glDeleteProgram(window.program); 

    glDeleteBuffers(1, &obj.vbo);

    return error;
}

void update(window_t &window, DrawObject &obj) {
    mat4 projection, view, rotation;
    cameraGetPerspective(window.cam, projection);
    cameraLookAt(window.cam, view);

    glUniformMatrix4fv(obj.projection_matrix, 1, GL_FALSE, 
        &projection[0][0]); 

    glUniformMatrix4fv(obj.view_matrix, 1, GL_FALSE, 
        &view[0][0]); 

    buildRotMatrix(rotation, window.cam.currentQuat);

    glEnable(GL_DEPTH);

    glUseProgram(window.program);

    glBindVertexArray(obj.vbo);

    glDrawElements(GL_TRIANGLES, obj.num, GL_UNSIGNED_INT, (void *) 0);

}

err_t InitScene(window_t &window) {
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

err_t managerSchedeuleTask(const event_t &event, event_data_t &data) {
}
