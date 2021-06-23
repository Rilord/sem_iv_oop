//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <memory>

#include <renderer/abstract_renderer.h>

class AbstractRendererFactory {
public:
    virtual std::unique_ptr<AbstractRenderer> create_graphics() = 0;
};