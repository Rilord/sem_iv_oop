//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <managers/transform_manager_creator.h>

std::shared_ptr<TransformManager> TransformManagerCreator::create_manager() {
    if (nullptr == _manager)
        create_instance();

    return _manager;
}

void TransformManagerCreator::create_instance() {
    static std::shared_ptr<TransformManager> manager(new TransformManager());

    _manager = manager;
}