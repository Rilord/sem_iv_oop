#ifndef DRAW_
#define DRAW_

#include "model.h"
#include <SDL2/SDL.h>

struct scene_view {
    
    SDL_Renderer *renderer;

    int width;
    int height;


};

struct mesh {
    vec3 a, b, c;
};

using scene_view_t = struct scene_view;
using mesh_t = struct mesh;

void draw_mesh(scene_view_t &view, mesh_t &mesh, vec3 &center);
int draw_model(model_t &model, scene_view_t &view);
#endif // DRAW_
