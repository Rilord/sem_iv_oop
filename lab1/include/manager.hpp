#ifndef MANAGER_H_
#define MANAGER_H_

#include "model.hpp"
#include "window.hpp"
#include "events.hpp"


int taskScheduler(camera_t &cam, DrawObject &obj, event_t &event);

int saveModelState(camera_t &cam);


#endif 
