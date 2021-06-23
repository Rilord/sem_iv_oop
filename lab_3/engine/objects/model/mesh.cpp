//
// Created by Kirill Diordiev on 25.05.2021.
//
#include <objects/model/mesh.h>

void ModelDetails::add_Vertex(const Vertex &pt) {
    _Vertexs.push_back(pt);
}

void ModelDetails::add_edge(const Polygon &link) {
    _edges.push_back(link);
}

const Vertex &ModelDetails::get_center() const {
    return _center;
}

const std::vector<Vertex> &ModelDetails::get_Vertexs() const {
    return _Vertexs;
}

const std::vector<Polygon> &ModelDetails::get_edges() const {
    return _edges;
}

void ModelDetails::transform(const Vertex &move, const Vertex &scale, const Vertex &rotate) {
    _center.move(move.get_x(), move.get_y(), move.get_z());

    for (auto &pt : _Vertexs) {
        pt.scale(scale.get_x(), scale.get_y(), scale.get_z());
        pt.rotate(rotate.get_x(), rotate.get_y(), rotate.get_z());
    }
}

ModelDetails::ModelDetails(std::vector<Vertex> &Vertexs, std::vector<Polygon> &edges) : _center{}, _Vertexs(Vertexs), _edges(edges) {}

ModelDetails::ModelDetails(Vertex &center, std::vector<Vertex> &Vertexs, std::vector<Polygon> &edges) : _center(center), _Vertexs(Vertexs), _edges(edges) {}