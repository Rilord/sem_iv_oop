#pragma once

#include <builder/base_builder.h>
#include <objects/model/mesh.h>
#include <objects/model/model.h>

namespace Load {
    class ModelBuilder : public BaseBuilder {
    public:
        ModelBuilder() = default;
        ~ModelBuilder() = default;

        [[nodiscard]] bool is_build() const override;
        void build() override;
        void build_Vertex(const double &x, const double &y, const double &z);
        void build_poly(const std::size_t &pt1, const std::size_t &pt2, const std::size_t &pt3);

        std::shared_ptr<Object> get() override;

    private:
        std::shared_ptr<ModelDetails> model_ptr;
    };
}// namespace Load