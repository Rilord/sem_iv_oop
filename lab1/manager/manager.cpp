#include "manager.h"
#include "draw.h"
#include "model.h"
#include "model_loader.h"
#include "model_transform.h"

int task_manager(const event_t& event, event_data_t& data) {
    int res = 0;

    static model_t model = model_init();

    switch (event.cmd) {
    case MOVE:
        res = move_model(model, data.move);
        break;
    case SCALE:
        res = scale_model(model, data.scale);
        break;
    case ROTATE:
        res = rotate_model(model, data.rotate);
        break;
    case DRAW:
        res = draw_model(model, data.view);
        break;
    case LOAD:
        res = scan_file(model, data.input_filename);
        break;
    case SAVE:
        res = save_to_file(model, data.output_filename);
        break;
    case QUIT:
        model_free(model);
        break;
    default:
        res = UNKNOWN;
        break;
    }

    return res;
}
