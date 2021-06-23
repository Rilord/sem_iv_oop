//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <loader/file_camera_loader.h>

#include <builder/scene_builder.h>
#include <error.h>
#include <errors/errors.h>


Load::FileCameraLoader::FileCameraLoader() : file(std::make_shared<std::ifstream>()) {}

Load::FileCameraLoader::FileCameraLoader(std::shared_ptr<std::ifstream> &fin) {
    file = fin;
}

std::shared_ptr<Object> Load::FileCameraLoader::load(const std::shared_ptr<CameraBuilder> &builder) {
    builder->build();

    double x, y, z;
    *file >> x >> y >> z;

    builder->build_position(x, y, z);

    return builder->get();
}

void Load::FileCameraLoader::open(std::string &fname) {
    if (!file) {
        std::string message = "Error while open file.";
        throw FileError(message);
    }
    file->open(fname);

    if (!file) {
        std::string message = "Error while open file.";
        throw FileError(message);
    }
}

void Load::FileCameraLoader::close() {
    if (!file) {
        std::string message = "Error while open file.";
        throw FileError(message);
    }

    try {
        file->close();
    } catch (std::ifstream::failure &error) {
        error.what();
    }
}