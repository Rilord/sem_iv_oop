//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <cstddef>

class Polygon
{
public:
    Polygon() = default;
    Polygon(const std::size_t &pt1, const std::size_t &pt2, const std::size_t &pt3);
    Polygon(const Polygon &_edge) = default;
    ~Polygon() = default;

    std::size_t get_fst() const;
    std::size_t get_snd() const;
    std::size_t get_last() const;

    void set_fst(const std::size_t &fst);
    void set_snd(const std::size_t &snd);
    void set_last(const std::size_t &snd);

private:
    std::size_t pt1_idx;
    std::size_t pt2_idx;
    std::size_t pt3_idx;
};