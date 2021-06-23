#include "mainwindow.h"
#include "draw.h"
#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl.h"
#include "imfilebrowser.h"
#include "manager.h"
#include <string>

#define WIDTH 800
#define HEIGHT 600
using std::string;

int main_window(const int window_width, const int window_height) {
    if (SDL_Init(SDL_INIT_VIDEO)) {
        return SDL_INIT_ERROR;
    }

    if (glewInit()) {
        return GLEW_INIT_ERROR;
    }

    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window, &renderer)) {
        return SDL_INIT_ERROR; 
    }

    SDL_GL_SetAttribute(
            SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE
            );

    SDL_GL_SetSwapInterval(1);

    glViewport(0, 0, window_width, window_height);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // setup Dear ImGui style
    ImGui::StyleColorsDark();

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL2_Init();

    ImVec4 background = ImVec4(35/255.0f, 35/255.0f, 35/255.0f, 1.00f);


    glClearColor(background.x, background.y, background.z, background.w);


    ImGui::FileBrowser fileDialog;
    string selectedFile;

    bool loop = true;

    float scale_data[3] = { 0.0, 0.0, 0.0 };
    float rotate_data[3] = { 0.0, 0.0, 0.0 };
    float move_data[3] = { 0.0, 0.0, 0.0 };

    while(loop) {
        glClear(GL_COLOR_BUFFER_BIT | 
                GL_DEPTH_BUFFER_BIT | 
                GL_STENCIL_BUFFER_BIT);

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);

        event_t event;
        event.cmd = ROTATE;

        ImGui::NewFrame();

        ImGui::Begin("Lab");


        ImGui::InputFloat3("Enter move data (x, y, z)", move_data);
        ImGui::InputFloat3("Enter scale data (kx, ky, kz):", scale_data);
        ImGui::InputFloat3("Enter rotate data (ax, ay, az)", rotate_data);


        ImVec4 clear_color(1.0, 1.0, 1.0, 1.0);


        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open..", "Ctrl+O"))
                {
                    fileDialog.Open();

                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if (ImGui::Button("Exit")) {
            event_t event;

            event_data_t event_data;
            event.cmd = QUIT;

            task_manager(event, event_data);

            loop = false;
        }

        if (ImGui::Button("Rotate")) {
            rotate_t rotate;
            rotate.ax = rotate_data[0];
            rotate.ay = rotate_data[1];
            rotate.az = rotate_data[2];
            event_data_t event_data;
            event_t event;
            event.cmd = ROTATE;
            event_data.rotate = rotate;

            int rc = task_manager(event, event_data);

            if (rc) {
                error_manager(rc);
            } else {
                scene_view_t view;
                view.width = window_width;
                view.height = window_height;
                view.renderer = renderer;
                event_t event;
                event.cmd = DRAW;
                event_data_t event_data;
                event_data.view = view;

                int rc = task_manager(event, event_data);

                if (rc) {
                    error_manager(rc);
                } 
            }
        }

        if (ImGui::Button("Scale")) {

            event_t event;
            scale_t scale;
            scale.kx = scale_data[0];
            scale.ky = scale_data[1];
            scale.kz = scale_data[2];
            event.cmd = SCALE;
            event_data_t event_data;
            event_data.scale = scale;

            int rc = task_manager(event, event_data);

            if (rc) {
                error_manager(rc);
            } else {
                scene_view_t view;
                view.width = window_width;
                view.height = window_height;
                view.renderer = renderer;
                event_t event;
                event.cmd = DRAW;
                event_data_t event_data;
                event_data.view = view;

                int rc = task_manager(event, event_data);

                if (rc) {
                    error_manager(rc);
                } 
            }
        }

        if (ImGui::Button("Move")) {
            event_t event;
            event.cmd = MOVE;
            move_t move;
            move.x = move_data[0];
            move.y = move_data[1];
            move.z = move_data[2];
            event_data_t event_data;

            int rc = task_manager(event, event_data);

            if (rc) {
                error_manager(rc);
            } else {
                scene_view_t view;
                view.width = window_width;
                view.height = window_height;
                view.renderer = renderer;
                event_t event;
                event.cmd = DRAW;
                event_data_t event_data;
                event_data.view = view;

                int rc = task_manager(event, event_data);

                if (rc) {
                    error_manager(rc);
                } 
            }
        }

        if (ImGui::Button("Draw")) {
            scene_view_t view;
            view.width = window_width;
            view.height = window_height;
            view.renderer = renderer;
            event_t event;
            event.cmd = DRAW;
            event_data_t event_data;
            event_data.view = view;

            int rc = task_manager(event, event_data);

            if (rc) {
                error_manager(rc);
            } 
        }

        if (ImGui::Button("Load")) {
            event_t event;
            event_data_t event_data;

            event.cmd = LOAD;
            event_data.input_filename = selectedFile.c_str();

            int rc = task_manager(event, event_data);

            if (rc) {
                error_manager(rc); 
            } else {
                scene_view_t view;
                view.width = window_width;
                view.height = window_height;
                view.renderer = renderer;
                event_t event;
                event.cmd = DRAW;
                event_data_t event_data;
                event_data.view = view;

                int rc = task_manager(event, event_data);

                if (rc) {
                    error_manager(rc);
                } 

            }

        }

        if (ImGui::Button("Save")) {
            event_t event;
            event_data_t event_data;

            event.cmd = SAVE;
            event_data.input_filename = selectedFile.c_str();

            int rc = task_manager(event, event_data);

            if (rc) {
                error_manager(rc); 
            } else {
                scene_view_t view;
                view.width = window_width;
                view.height = window_height;
                view.renderer = renderer;
                event_t event;
                event.cmd = DRAW;
                event_data_t event_data;
                event_data.view = view;

                int rc = task_manager(event, event_data);

                if (rc) {
                    error_manager(rc);
                } 

        }

        fileDialog.Display();

        if(fileDialog.HasSelected())
        {
            selectedFile = fileDialog.GetSelected();
            fileDialog.ClearSelected();
        }

        ImGui::End();

        ImGui::Render();

        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);
    }
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

