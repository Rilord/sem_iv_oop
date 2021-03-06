//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <load_controller/scene_load_controller.h>

#include <error.h>

std::shared_ptr<Object> Load::SceneLoadController::load(std::string &fname) {
    try {
        loader->open(fname);
    } catch (SourceError &error) {
        throw SourceError((std::string &) "can't open source");
    }

    std::shared_ptr<Object> scene;
    try {
        scene = loader->load(builder);
    } catch (std::exception &error) {
        throw SourceError((std::string &) "can't read model");
    }

    loader->close();

    return scene;
}
