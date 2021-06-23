//
// Created by Kirill Diordiev on 30.05.2021.
//

#pragma once

#include <builder/camera_builder.h>
#include <loader/base_loader.h>

namespace Load {
    class BaseCameraLoader : public BaseLoader {
    public:
        virtual std::shared_ptr<Object> load(const std::shared_ptr<CameraBuilder> &builder) = 0;
    };
}// namespace Load