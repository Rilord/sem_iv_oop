//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <objects/composite/composite.h>

Composite::Composite(std::shared_ptr <Object> &component) {
    objects.push_back(component);
}

Composite::Composite(const std::vector <std::shared_ptr<Object>> &vector) {
    objects = vector;
}

bool Composite::add(const std::shared_ptr <Object> &component) {
    objects.push_back(component);
    return true;
}

bool Composite::remove(const Iterator &iter) {
    objects.erase(iter);
    return true;
}

Iterator Composite::begin() {
    return objects.begin();
}

Iterator Composite::end() {
    return objects.end();
}

bool Composite::is_visible() {
    return false;
}

bool Composite::is_composite() const {
    return true;
}

void Composite::transform(const Vertex &move, const Vertex &scale, const Vertex &rotate) {
    for (const auto &element : objects) {
        element->transform(move, scale, rotate);
    }
}

void Composite::accept(std::shared_ptr <Spectator> visitor) {
    for (const auto &element : objects) {
        element->accept(visitor);
    }
}

