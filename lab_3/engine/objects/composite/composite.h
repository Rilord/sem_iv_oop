//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <objects/object.h>
#include <scene/scene.h>
#include <spectator/spectator.h>

class Composite : public Object {
    friend std::vector<std::shared_ptr<Object>> Scene::get_models();
public:
    Composite() = default;
    explicit Composite(std::shared_ptr<Object> &component);
    explicit Composite(const std::vector<std::shared_ptr<Object>> &vector);


    bool add(const std::shared_ptr<Object> &component) override;
    bool remove(const Iterator &iterator) override;

    Iterator begin() override;
    Iterator end() override;

    bool is_visible() override;
    bool is_composite() const override;
    void transform(const Vertex &move, const Vertex &scale, const Vertex &turn) override;
    void accept(std::shared_ptr<Spectator> Spectator) override;


protected:
    std::vector<std::shared_ptr<Object>> objects;
};
