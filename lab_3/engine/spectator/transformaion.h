//
// Created by Kirill Diordiev on 11.06.2021.
//

#pragma once

#include <cmath>
#include <objects/matrix.h>
#include <objects/model/vertex.h>

class MoveMatrix : public Matrix<double>
{
public:
    MoveMatrix(double x, double y, double z);
    MoveMatrix(Vertex p);
};

class ScaleMatrix : public Matrix<double>
{
public:
    ScaleMatrix(double x, double y, double z);
    ScaleMatrix(Vertex p);
};

class RotateOxMatrix : public Matrix<double>
{
public:
    RotateOxMatrix(double angle);
};

class RotateOyMatrix : public Matrix<double>
{
public:
    RotateOyMatrix(double angle);
};

class RotateOzMatrix : public Matrix<double>
{
public:
    RotateOzMatrix(double angle);
};
