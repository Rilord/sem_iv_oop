#ifndef EVENTS_H_
#define EVENTS_H_

#include "model_loader.hpp"

enum commands {
    MOVE,
    ROTATE,
    LOAD,
    SAVE,
    UNKNOWN,
    STILL
};

typedef struct {
    float x, y, z;
    string filename;
} event_data_t;

typedef struct {
    commands cmd;
    event_data_t data;
} event_t;



#endif /* EVENTS_H_ */
