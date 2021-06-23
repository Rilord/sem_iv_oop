#include <builder/model_builder.h>

bool Load::ModelBuilder::is_build() const {
    return nullptr != model_ptr;
}

void Load::ModelBuilder::build() {
    model_ptr = std::make_shared<ModelDetails>();
}

void Load::ModelBuilder::build_Vertex(const double &x, const double &y, const double &z) {
    if (!is_build()) {}

    Vertex pt_obj(x, y, z);
    model_ptr->add_Vertex(pt_obj);
}

void Load::ModelBuilder::build_poly(const std::size_t &pt1, const std::size_t &pt2, const std::size_t &pt3) {
    if (!is_build()) {}

    Polygon edge_obj(pt1, pt2, pt3);
    model_ptr->add_edge(edge_obj);
}

std::shared_ptr<Object> Load::ModelBuilder::get() {
    return std::make_shared<Model>(Model(model_ptr));
}