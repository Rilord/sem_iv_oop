#ifndef MANAGER_
#define MANAGER_

#include "commands.h"
#include "draw.h"
#include "vertex_array_transform.h"
#include "SDL2/SDL.h"

struct event {
    commands_t cmd;    
};

struct event_data {
    scene_view_t view;
    move_t move;
    scale_t scale;
    rotate_t rotate;

    const char *output_filename;
    const char *input_filename;
};

using event_t = struct event;
using event_data_t = struct event_data;

int task_manager(const event_t& event, event_data_t& data);

#endif // MANAGER_
