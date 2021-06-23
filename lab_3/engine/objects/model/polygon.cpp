//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <objects/model/polygon.h>

Polygon::Polygon(const std::size_t &pt1, const std::size_t &pt2, const std::size_t &pt3) :
pt1_idx(pt1), pt2_idx(pt2), pt3_idx(pt3) {};

std::size_t Polygon::get_fst() const {
    return pt1_idx;
}

std::size_t Polygon::get_snd() const {
    return pt2_idx;
}

std::size_t Polygon::get_last() const {
    return pt3_idx;
}

void Polygon::set_fst(const std::size_t &fst) {
    pt1_idx = fst;
}

void Polygon::set_snd(const std::size_t &snd) {
    pt2_idx = snd;
}

void Polygon::set_last(const std::size_t &snd) {
    pt3_idx = snd;
}
