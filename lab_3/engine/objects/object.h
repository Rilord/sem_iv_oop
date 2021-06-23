//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <memory>

#include <spectator/spectator.h>

#include <objects/model/vertex.h>

#include <vector>

class Object;

using Iterator = std::vector<std::shared_ptr<Object>>::iterator;

class Object {
public:
    Object() = default;
    virtual ~Object() = default;

    virtual bool add(const std::shared_ptr<Object> &) { return false; };
    virtual bool remove(const Iterator &) { return false; };

    virtual Iterator begin() { return Iterator(); };
    virtual Iterator end() { return Iterator(); };

    virtual bool is_visible() { return false; }
    virtual bool is_composite() const { return false; };
    virtual void accept(std::shared_ptr<Spectator> Spectator) = 0;
    virtual void transform(const Vertex &move, const Vertex &scale, const Vertex &turn) = 0;
};

class VisibleObject : public Object {
public:
    VisibleObject() = default;
    ~VisibleObject() override = default;

    bool is_visible() override { return true; }
};

class InvisibleObject : public Object {
public:
    InvisibleObject() = default;
    ~InvisibleObject() override = default;

    bool is_visible() override { return false; }
};