//
// Created by Kirill Diordiev on 30.05.2021.
//

#include <qt_render.h>

QtRenderer::QtRenderer(QGraphicsScene *_scene)  : scene(_scene){}

QtRenderer::QtRenderer(const QtRenderer &_Renderer) : scene(_Renderer.scene) {}

void QtRenderer::clear_scene() {
    scene->clear();
}

void QtRenderer::render_line(const Vertex &Vertex1, const Vertex &Vertex2) {
    scene->addLine(Vertex1.get_x(), Vertex1.get_y(), Vertex2.get_x(), Vertex2.get_y());
}