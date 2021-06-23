//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <managers/scene_manager_creator.h>

std::shared_ptr<SceneManager> SceneManagerCreator::create_manager() {
    if (nullptr == _manager)
        create_instance();

    return _manager;
}

void SceneManagerCreator::create_instance() {
    static std::shared_ptr<SceneManager> manager(new SceneManager());

    _manager = manager;
}