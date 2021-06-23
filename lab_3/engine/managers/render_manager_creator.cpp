//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <managers/render_manager_creator.h>

std::shared_ptr<RenderManager> RenderManagerCreator::create_manager() {
    if (nullptr == _manager)
        create_instance();

    return _manager;
}

void RenderManagerCreator::create_instance() {
    static std::shared_ptr<RenderManager> manager(new RenderManager());

    _manager = manager;
}