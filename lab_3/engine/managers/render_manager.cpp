//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <managers/render_manager.h>

#include <utility>

#include <objects/model/model.h>
#include <objects/camera/camera.h>

void RenderManager::set_renderer(std::shared_ptr<AbstractRenderer> renderer) {
    _renderer = std::move(renderer);
}

void RenderManager::set_cam(std::shared_ptr<Camera> new_cam) {
    _camera = std::move(new_cam);
}

void RenderManager::draw(std::shared_ptr<Scene> _scene) {
        _scene->get_models()->accept(std::shared_ptr<Spectator>(new Spectator(_camera, _renderer)));

}