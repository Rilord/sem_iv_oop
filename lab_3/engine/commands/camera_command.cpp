//
// Created by Kirill Diordiev on 25.05.2021.
//

#include "camera_command.h"
#include <objects/camera/camera.h>

#include <commands/camera_command.h>
#include <managers/transform_manager_creator.h>
#include <managers/scene_manager_creator.h>

#define cd const double

AddCamera::AddCamera(cd _x, cd _y, cd _z) : x(_x), y(_y), z(_z) {}

void AddCamera::execute() {
    Vertex cam_pos(x, y, z);

    std::shared_ptr<Camera> cam(new Camera);
    cam->transform(cam_pos, cam_pos, cam_pos);

    auto _scene_manager = SceneManagerCreator().create_manager();
    _scene_manager->get_scene()->add_camera(cam);
    _scene_manager->set_cam(_scene_manager->get_scene()->get_cams().size() - 1);
}

RemoveCamera::RemoveCamera(const std::size_t &camera_numb) : camera_numb(camera_numb) {}

void RemoveCamera::execute() {
    SceneManagerCreator().create_manager()->get_scene()->remove_camera(camera_numb);
}

MoveCamera::MoveCamera(const std::size_t &cam_number, cd &shift_ox, cd &shift_oy) : cam_number(cam_number), shift_ox(shift_ox), shift_oy(shift_oy) {}

void MoveCamera::execute() {
    Vertex shift(shift_ox, shift_oy, 0);
    auto camera = SceneManagerCreator().create_manager()->get_scene()->get_cams().at(cam_number);
    TransformManagerCreator().create_manager()->transform_object(camera, shift, shift, shift);
}

SetCamera::SetCamera(const std::size_t &cam_number) : cam_number(cam_number) {}

void SetCamera::execute() {
    SceneManagerCreator().create_manager()->set_cam(cam_number);
}

CameraCount::CameraCount(std::shared_ptr<size_t> &count) : _count(count) {}

void CameraCount::execute() {
    (*_count) = SceneManagerCreator().create_manager()->get_scene()->get_cams().size();
}