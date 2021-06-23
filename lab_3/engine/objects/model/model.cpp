//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <objects/model/model.h>

#include <memory>

Model::Model(const Model &_model) {
    _details = _model._details;
}

void Model::transform(const Vertex &move_coeff, const Vertex &scale_coeff, const Vertex &turn_coeff) {
    _details->transform(move_coeff, scale_coeff, turn_coeff);
}

void Model::accept(std::shared_ptr<Spectator> _visitor) {
    _visitor->spectate(*this);
}