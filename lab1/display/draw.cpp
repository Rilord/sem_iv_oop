#include "draw.h"
#include "edge_array.h"
#include "model.h"
#include "vertex_array.h"


void draw_mesh(scene_view_t &view, mesh_t &mesh, vec3 &center) {
    mesh.a.x += center.x;
    mesh.a.y += center.y;
    mesh.b.x += center.x;
    mesh.b.y += center.y;
    mesh.c.x += center.x;
    mesh.c.y += center.y;

    SDL_SetRenderDrawColor(view.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    SDL_RenderDrawLine(view.renderer, mesh.a.x, mesh.a.y, mesh.b.x, mesh.b.y);

    SDL_RenderDrawLine(view.renderer, mesh.b.x, mesh.b.y, mesh.c.x, mesh.c.y);

    SDL_RenderDrawLine(view.renderer, mesh.a.x, mesh.a.y, mesh.c.x, mesh.c.y);

}
int draw_model(model_t &model, scene_view_t &view) {
    vertex_array_t vertices = get_vertex_arr(model);
    face_array_t faces = get_face_arr(model);


    if (vertices.vertices == nullptr || faces.faces == nullptr) {
        return 303;
    }

    SDL_RenderClear(view.renderer);


    for (unsigned int i = 0; i < face_array_len(faces); i++) {
        face_t face = get_face(faces, i);

        vec3 a = get_dot(vertices, face.i1);
        vec3 b = get_dot(vertices, face.i2);
        vec3 c = get_dot(vertices, face.i3);
        mesh_t mesh;

        mesh.a = a; mesh.b = b; mesh.c = c;

        vec3 center = get_center(model);


        draw_mesh(view, mesh, center);
    }

    SDL_RenderPresent(view.renderer);
    return SUCCESS;
}

