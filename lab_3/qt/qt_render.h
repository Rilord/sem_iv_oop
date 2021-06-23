//
// Created by Kirill Diordiev on 30.05.2021.
//

#pragma once

#include <QGraphicsScene>

#include <renderer/abstract_renderer.h>

class QtRenderer : public AbstractRenderer {
public:
    QtRenderer() = delete;
    explicit QtRenderer(QGraphicsScene *_scene);
    QtRenderer(const QtRenderer &_Renderer);

    void render_line(const Vertex &Vertex1, const Vertex &Vertex2) override;
    void clear_scene() override;

private:
    QGraphicsScene *scene;
};