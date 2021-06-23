//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <builder/model_builder.h>
#include <loader/base_loader.h>

namespace Load {
    class BaseModelLoader : public BaseLoader {
    public:
        virtual std::shared_ptr<Object> load(std::shared_ptr<ModelBuilder> builder) = 0;
    };
}// namespace Load