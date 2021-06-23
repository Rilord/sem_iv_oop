//
// Created by Kirill Diordiev on 25.05.2021.
//


#pragma once

#include <memory>

#include <managers/render_manager.h>

class RenderManagerCreator {
public:
    std::shared_ptr<RenderManager> create_manager();

private:
    void create_instance();

    std::shared_ptr<RenderManager> _manager;
};