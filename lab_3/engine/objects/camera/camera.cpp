//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <objects/camera/camera.h>

void Camera::move_x(const double &shift) {
    current_pos.set_x(current_pos.get_x() + shift);
}

void Camera::move_y(const double &shift) {
    current_pos.set_y(current_pos.get_y() + shift);
}

void Camera::move_z(const double &shift) {
    current_pos.set_z(current_pos.get_z() + shift);
}

void Camera::transform(const Vertex &new_pos, const Vertex &scale, const Vertex &turn) {
    move_x(new_pos.get_x());
    move_y(new_pos.get_y());
}

void Camera::accept(std::shared_ptr<Spectator> _visitor) {
    _visitor->spectate(shared_ptr<Camera>(this));
}

double Camera::getX() const
{
    return current_pos.getX();
}

double Camera::getY() const
{
    return current_pos.getY();
}

double Camera::getZ() const
{
    return current_pos.getZ();
}

void Camera::setX(const double x)
{
    current_pos.setX(x);
}

void Camera::setY(const double y)
{
    current_pos.setY(y);
}



void Camera::setZ(const double z)
{
    current_pos.setZ(z);
}
