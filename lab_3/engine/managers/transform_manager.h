//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <managers/base_manager.h>
#include <objects/object.h>

class TransformManager : public BaseManager {
public:
    TransformManager() = default;
    TransformManager(const TransformManager &) = delete;
    TransformManager &operator=(const TransformManager &) = delete;
    ~TransformManager() = default;

    static void transform_object(const std::shared_ptr<Object> &_object, const Vertex &move, const Vertex &scale, const Vertex &turn);

    static void move_object(const std::shared_ptr<Object> &_object, const double &dx, const double &dy, const double &dz);
    static void scale_object(const std::shared_ptr<Object> &_object, const double &kx, const double &ky, const double &kz);
    static void turn_object(const std::shared_ptr<Object> &_object, const double &ox, const double &oy, const double &oz);
};