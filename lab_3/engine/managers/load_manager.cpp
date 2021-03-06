#include <managers/load_manager.h>

#include <load_controller/model_load_controller.h>
#include <load_controller/scene_load_controller_creator.h>
#include <loader/file_model_loader.h>
#include <utility>

Load::LoadManager::LoadManager() {
    loader = SceneLoadControllerCreator().create_controller();
}

void Load::LoadManager::set_loader(std::shared_ptr<AbstractLoadController> _loader) { loader = std::move(_loader); }

std::shared_ptr<Object> Load::LoadManager::load(std::string &name) {
    return loader->load(name);
}
