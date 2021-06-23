//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <memory>

#include <managers/scene_manager.h>

class SceneManagerCreator {
public:
    std::shared_ptr<SceneManager> create_manager();

private:
    void create_instance();

    std::shared_ptr<SceneManager> _manager;
};