#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "draw.h"
#include "manager.h"
#include "errors.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl.h"
#include "imgui.h"

#define SDL_INIT_ERROR 21
#define GLEW_INIT_ERROR 22

int main_window(const int window_width, const int window_height);
