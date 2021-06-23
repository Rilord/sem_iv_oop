//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <objects/model/vertex.h>

class AbstractRenderer {
public:
    AbstractRenderer() = default;
    virtual ~AbstractRenderer() = default;
    virtual void render_line(const Vertex &p1, const Vertex &p2) = 0;
    virtual void clear_scene() = 0;
};