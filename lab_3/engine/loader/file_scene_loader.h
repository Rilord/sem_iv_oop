//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <loader/base_scene_loader.h>

namespace Load {
    class FileSceneLoader : public BaseSceneLoader {
    public:
        FileSceneLoader();
        ~FileSceneLoader() override = default;
        std::shared_ptr<Object> load(const std::shared_ptr<SceneBuilder> &builder) override;

    public:
        void open(std::string &fname) override;
        void close() override;

    protected:
        std::shared_ptr<std::ifstream> file;

    protected:
        void load_models(std::shared_ptr<SceneBuilder> builder) override;
        void load_cameras(std::shared_ptr<SceneBuilder> builder) override;
    };
}// namespace Load