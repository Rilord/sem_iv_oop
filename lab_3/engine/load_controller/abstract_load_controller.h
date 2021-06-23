//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <memory>
#include <utility>

#include <builder/base_builder.h>
#include <loader/base_loader.h>

namespace Load {
    class AbstractLoadController {
    public:
        AbstractLoadController() = default;
        ~AbstractLoadController() = default;

        virtual std::shared_ptr<Object> load(std::string &name) = 0;
        virtual void set_loader(std::shared_ptr<BaseLoader> _loader);

    protected:
        std::shared_ptr<BaseLoader> loader;
    };
}// namespace Load