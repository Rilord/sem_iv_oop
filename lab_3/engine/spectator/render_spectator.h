//
// Created by Kirill Diordiev on 09.06.2021.
//

#pragma once

#include <spectator/spectator.h>
#include <objects/model/model.h>

#include <memory>

using namespace std;

class TransformSpectator : public Spectator
{
public:
    TransformSpectator(const double x, const double y, const double z);

protected:
    double p1;
    double p2;
    double p3;
};

class MoveSpectator : public TransformSpectator
{
public:
    MoveSpectator(const double x, const double y, const double z);

    void spectate(shared_ptr<Composite> obj) override;
    void spectate(shared_ptr<Model> model) override;
    void spectate(shared_ptr<Camera> camera) override;
};


class ScaleSpectator: public TransformSpectator
{
public:
    ScaleSpectator(const double x, const double y, const double z);

    void spectate(shared_ptr<Composite> obj) override;
    void spectate(shared_ptr<Model> model) override;
    void spectate(shared_ptr<Camera> camera) override;
};

class RotateSpectator: public TransformSpectator
{
public:
    RotateSpectator(const double x, const double y, const double z);

    void spectate(shared_ptr<Composite> obj) override;
    void spectate(shared_ptr<Model> model) override;
    void spectate(shared_ptr<Camera> camera) override;
protected:
    void rotateX(double& y, double& z, double a);
    void rotateY(double& x, double& z, double a);
    void rotateZ(double& x, double& y, double a);
};