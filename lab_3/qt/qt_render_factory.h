//
// Created by Kirill Diordiev on 30.05.2021.
//

#pragma once

#include <memory>

#include <config/abstract_config.h>

#include <renderer/abstract_render_factory.h>
#include <qt_render.h>


class QtRendererFactory : public AbstractRendererFactory {
public:
    explicit QtRendererFactory(QGraphicsScene *scene);

    std::unique_ptr<AbstractRenderer> create_graphics() override {
        return std::unique_ptr<AbstractRenderer>(new QtRenderer(_scene));
    }

private:
    QGraphicsScene *_scene;
    std::shared_ptr<AbstractConfiguration> _conf;
};