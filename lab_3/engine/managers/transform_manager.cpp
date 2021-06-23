//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <managers/transform_manager.h>

void TransformManager::transform_object(const std::shared_ptr<Object>& _object,
                                        const Vertex &move,
                                        const Vertex &scale,
                                        const Vertex &turn) {
    _object->transform(move, scale, turn);
}

void TransformManager::move_object(const std::shared_ptr<Object>& _object,
                                   const double &dx,
                                   const double &dy,
                                   const double &dz) {
    Vertex move(dx, dy, dz);
    Vertex scale(1, 1, 1);
    Vertex turn(0, 0, 0);

    _object->transform(move, scale, turn);
}

void TransformManager::scale_object(const std::shared_ptr<Object>& _object,
                                    const double &kx,
                                    const double &ky,
                                    const double &kz) {
    Vertex move(0, 0, 0);
    Vertex scale(kx, ky, kz);
    Vertex turn(0, 0, 0);

    _object->transform(move, scale, turn);
}

void TransformManager::turn_object(const std::shared_ptr<Object>& _object,
                                   const double &ox,
                                   const double &oy,
                                   const double &oz) {
    Vertex move(0, 0, 0);
    Vertex scale(1, 1, 1);
    Vertex turn(ox, oy, oz);

    _object->transform(move, scale, turn);
}