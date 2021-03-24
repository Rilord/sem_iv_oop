#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "errors.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "implot.h"
#include "imfilebrowser.h"
#include "model.hpp"
#include "window.hpp"
#include "model_loader.hpp"
#include "shaders.hpp"
#include <iostream>
#include <string>


int main(int argc, char *argv[])
{
    window_t MainWindow;
    model_t model;
    DrawObject obj;
    auto err = SUCCESS;

    if (argv[1] == NULL) {
        fprintf(stderr, "Wrong File!");
        return 1;
    }

    string filename = { argv[1], 
        strlen(argv[1])};

    if ((err = startWindowContext(MainWindow, 800, 600)) != SUCCESS)
    {
        ErrorHandler(err);
        return 1;
    }

    setCallbacks(MainWindow);

    if ((err = runGLEW()) != SUCCESS) {
        ErrorHandler(err);
        return 1;
    }

    if ((err = parseVertexFile(model, filename)) != SUCCESS) {
        ErrorHandler(err);
        return 1;
    }

    if ((err = initImGui(MainWindow)) != SUCCESS) {
        ErrorHandler(err);
        DestroyData(model);
        return 1;
    }

    if ((err = InitScene(MainWindow)) != SUCCESS) {
        ErrorHandler(err);
        DestroyData(model);
        return 1;
    }

    if ((err = LoadShader(MainWindow.program)) != SUCCESS) {
        ErrorHandler(err);
        destroyDrawObject(MainWindow, obj);
        DestroyData(model);
        return 1;
    }

    if ((err = loadVertexBuffer(obj, model, MainWindow.program)) != SUCCESS) {
        destroyDrawObject(MainWindow, obj);
        DestroyData(model);
        ErrorHandler(err);
        return 1;
        
    }

    DestroyData(model);

    if (runLoop(MainWindow, obj)) {
        destroyDrawObject(MainWindow, obj);
        DestroyData(model);
        ErrorHandler(err);
    }

    destroyDrawObject(MainWindow, obj);

    return 0;
}
