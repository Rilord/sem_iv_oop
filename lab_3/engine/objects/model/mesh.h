//
// Created by Kirill Diordiev on 25.05.2021.
//


#pragma once

#include <vector>

#include <objects/model/polygon.h>
#include <objects/model/vertex.h>

class ModelDetails {
public:
    ModelDetails() = default;
    ModelDetails(std::vector<Vertex> &_Vertexs, std::vector<Polygon> &_edges);
    ModelDetails(Vertex &center, std::vector<Vertex> &Vertexs, std::vector<Polygon> &edges);
    ~ModelDetails() = default;

    void add_Vertex(const Vertex &pt);
    void add_edge(const Polygon &edge);
    [[nodiscard]] const Vertex &get_center() const;
    [[nodiscard]] const std::vector<Vertex> &get_Vertexs() const;
    [[nodiscard]] const std::vector<Polygon> &get_edges() const;

    void transform(const Vertex &move, const Vertex &scale, const Vertex &rotate);

private:
    Vertex _center;

    std::vector<Vertex> _Vertexs;
    std::vector<Polygon> _edges;
};