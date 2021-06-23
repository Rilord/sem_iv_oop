//
// Created by Kirill Diordiev on 09.06.2021.
//

#include <spectator/render_spectator.h>

#include <objects/camera/camera.h>
#include <objects/model/model.h>

#include <math.h>

TransformSpectator::TransformSpectator(const double x, const double y, const double z)
{
    this->p1 = x;
    this->p2 = y;
    this->p3 = z;
}

MoveSpectator::MoveSpectator(const double x, const double y, const double z) : TransformSpectator(x, y, z)
{}

void MoveSpectator::spectate(shared_ptr<CompositeObject> obj)
{
    for (auto cur: *(obj.get()))
        cur->accept(this);
}

void MoveSpectator::spectate(shared_ptr<FrameModel> model)
{
    model->accept(this);
}

void MoveSpectator::spectate(shared_ptr<Camera> camera)
{
    double x = camera->getX();
    double y = camera->getY();
    double z = camera->getZ();

    x += p1;
    y += p2;
    z += p3;

    camera->setX(x);
    camera->setY(y);
    camera->setZ(z);
}

void MoveSpectator::spectate(Vertex &point)
{
    double x = point.getX();
    double y = point.getY();
    double z = point.getZ();

    x += p1;
    y += p2;
    z += p3;

    point.setX(x);
    point.setY(y);
    point.setZ(z);
}



ScaleSpectator::ScaleSpectator(const double x, const double y, const double z) : TransformSpectator(x, y, z)
{}

void ScaleSpectator::spectate(shared_ptr<CompositeObject> obj)
{
    for (auto cur: *(obj.get()))
        cur->accept(this);
}

void ScaleSpectator::spectate(shared_ptr<FrameModel> model)
{
    model->accept(this);
}

void ScaleSpectator::spectate(shared_ptr<Camera> camera)
{
    double x = camera->getX();
    double y = camera->getY();
    double z = camera->getZ();

    x *= p1;
    y *= p2;
    z *= p3;

    camera->setX(x);
    camera->setY(y);
    camera->setZ(z);
}


RotateSpectator::RotateSpectator(const double x, const double y, const double z) : TransformSpectator(x, y, z)
{}

void RotateSpectator::spectate(shared_ptr<Composite> obj)
{
    for (auto cur: *(obj.get()))
        cur->accept(this);
}

void RotateSpectator::spectate(shared_ptr<Model> model)
{
    model->accept(this);
}

void RotateSpectator::spectate(shared_ptr<Camera> camera)
{
    double x = camera->getX();
    double y = camera->getY();
    double z = camera->getZ();

    rotateX(y, z, p1);
    rotateY(x, z, p2);
    rotateZ(x, y, p3);

    camera->setX(x);
    camera->setY(y);
    camera->setZ(z);
}


void RotateSpectator::rotateX(double &y, double &z, double a)
{
    double _y = y * cos(a) - z * sin(a);
    double _z = y * sin(a) + z * cos(a);
    y = _y;
    z = _z;
}

void RotateSpectator::rotateY(double &x, double &z, double a)
{
    double _x = x * cos(a) + z * sin(a);
    double _z = -x * sin(a) + z * cos(a);
    x = _x;
    z = _z;
}

void RotateSpectator::rotateZ(double &x, double &y, double a)
{
    float _x = x * cos(a) - y * sin(a);
    float _y = x * sin(a) + y * cos(a);
    x = _x;
    y = _y;
}
