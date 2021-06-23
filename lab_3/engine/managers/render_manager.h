//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <memory>

#include <renderer/abstract_renderer.h>
#include <managers/base_manager.h>
#include <objects/composite/composite.h>
#include <objects/model/vertex.h>
#include <spectator/spectator.h>
#include <spectator/render_spectator.h>

class RenderManager : public BaseManager {
public:
    RenderManager() = default;
    RenderManager(const RenderManager &) = delete;
    RenderManager &operator=(const RenderManager &) = delete;
    ~RenderManager() = default;


    void set_renderer(std::shared_ptr<AbstractRenderer>);
    void set_cam(std::shared_ptr<Camera>);

    void draw(std::shared_ptr<Scene> _scene);


    Vertex proect_Vertex(const Vertex &vertex);

private:
    std::shared_ptr<Spectator> _visitor;
    std::shared_ptr<AbstractRenderer> _renderer;
    std::shared_ptr<Camera> _camera;

};