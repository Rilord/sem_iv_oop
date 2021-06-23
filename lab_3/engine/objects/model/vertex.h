//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

class Vertex {
public:
    Vertex() = default;
    Vertex(const double x, const double y, const double z);

    Vertex(const Vertex &Vertex) = default;
    Vertex &operator=(const Vertex &Vertex) = default;

    Vertex(const Vertex &&Vertex) noexcept;
    Vertex &operator=(Vertex &&Vertex) noexcept;

    bool operator==(const Vertex &Vertex) const noexcept;
    [[nodiscard]] bool equals(const Vertex &Vertex) const noexcept;
    bool operator!=(const Vertex &Vertex) const noexcept;

    ~Vertex() = default;

    [[nodiscard]] double get_x() const;
    [[nodiscard]] double get_y() const;
    [[nodiscard]] double get_z() const;

    void set_x(double const &x);
    void set_y(double const &y);
    void set_z(double const &z);

    Vertex operator+(const Vertex &p);
    Vertex operator-(const Vertex &p);

    Vertex relative_to(const Vertex &c);

    void move(const double dx, const double dy, const double dz);
    void scale(const double kx, const double ky, const double kz);
    void rotate(const double ox, const double oy, const double oz);

    void rotate_x(const double &ox);
    void rotate_y(const double &oy);
    void rotate_z(const double &oz);

private:
    double _x, _y, _z;
};