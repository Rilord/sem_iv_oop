//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <memory>

#include <managers/transform_manager.h>

class TransformManagerCreator {
public:
    std::shared_ptr<TransformManager> create_manager();

private:
    void create_instance();

    std::shared_ptr<TransformManager> _manager;
};