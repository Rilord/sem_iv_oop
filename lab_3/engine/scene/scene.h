//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <vector>
#include <objects/object.h>

class Scene : public Object {
public:
    Scene();
    ~Scene() override = default;

    void add_model(const std::shared_ptr<Object> &model);
    void remove_model(const std::size_t model_index);

    void add_camera(const std::shared_ptr<Camera> &camera);
    void remove_camera(const std::size_t cam_index);

    std::vector<std::shared_ptr<Object>> get_models();
    std::shared_ptr<Composite> get_composite();
    std::vector<std::shared_ptr<Camera>> get_cams();

protected:
    std::shared_ptr<Composite> models;
    std::vector<std::shared_ptr<Camera>> cams;

private:
    void accept(std::shared_ptr<Spectator> Spectator) override {};
    void transform(const Vertex &move, const Vertex &scale, const Vertex &turn) override {};
};