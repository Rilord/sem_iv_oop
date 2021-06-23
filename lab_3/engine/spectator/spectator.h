//
// Created by Kirill Diordiev on 30.05.2021.
//

#pragma once

#include <memory>
#include <renderer/abstract_renderer.h>

using namespace std;

class Camera;
class Model;
class Composite;

class Spectator
{
    Spectator() = default;
    Spectator(const std::shared_ptr<Camera> &_camera, const std::shared_ptr<AbstractRenderer> _renderer);
    ~Spectator() =default;

    void spectate_model(Model &_model);
    void spectate_camera(Camera &_camera) {};

private:
    Vertex get_projection(Vertex &_point);
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<AbstractRenderer> _renderer;
};