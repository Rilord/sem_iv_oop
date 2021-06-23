//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <objects/object.h>
#include <spectator/render_spectator.h>
#include <managers/render_manager.h>

class Camera : public InvisibleObject {
    friend Vertex RenderManager::proect_Vertex(const Vertex &vertex);

public:
    Camera() = default;
    explicit Camera(const Vertex &pos) : current_pos(pos){};
    ~Camera() override = default;

    void transform(const Vertex &pos, const Vertex &turn, const Vertex &scale) override;
    void accept(std::shared_ptr<Spectator> spectator) override;

    double getX() const;
    double getY() const;
    double getZ() const;

    void setX(const double x);
    void setY(const double y);
    void setZ(const double z);

protected:
    Vertex current_pos;

private:
    void move_x(const double &shift);
    void move_y(const double &shift);
    void move_z(const double &shift);

};