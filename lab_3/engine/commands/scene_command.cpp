//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <commands/scene_command.h>

#include <load_controller/scene_load_controller_creator.h>
#include <managers/render_manager_creator.h>
#include <managers/load_manager_creator.h>
#include <managers/scene_manager.h>
#include <managers/scene_manager_creator.h>
#include <utility>

RenderScene::RenderScene(std::shared_ptr<AbstractRenderer> Renderer) : _Renderer(std::move(Renderer)) {
}

void RenderScene::execute() {
    auto _Render_manager = RenderManagerCreator().create_manager();
    auto _scene_manager = SceneManagerCreator().create_manager();

    _Renderer->clear_scene();
    _Render_manager->set_renderer(_Renderer);
    _Render_manager->set_cam(_scene_manager->get_cam());
    _scene_manager->get_scene()->get_composite()->accept(_Render_manager);
}

LoadScene::LoadScene(std::string fname) : _fname(std::move(fname)) {}

void LoadScene::execute() {
    auto controller = Load::SceneLoadControllerCreator().create_controller();

    auto manager = Load::LoadManagerCreator().create_manager(controller);

    auto scene = std::dynamic_pointer_cast<Scene>(manager->load(_fname));
    SceneManagerCreator().create_manager()->set_scene(scene);
}
