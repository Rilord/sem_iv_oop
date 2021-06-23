//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <builder/model_builder.h>
#include <error.h>
#include <errors/errors.h>
#include <loader/file_model_loader.h>

Load::FileModelLoader::FileModelLoader() : file(std::make_shared<std::ifstream>()) {}

Load::FileModelLoader::FileModelLoader(std::shared_ptr<std::ifstream> &fin) {
    file = fin;
}

std::shared_ptr<Object> Load::FileModelLoader::load(std::shared_ptr<ModelBuilder> builder) {
    builder->build();

    std::size_t Vertexs_count;
    *file >> Vertexs_count;

    for (std::size_t i = 0; i < Vertexs_count; i++) {
        double x, y, z;
        *file >> x >> y >> z;
        builder->build_Vertex(x, y, z);
    }

    std::size_t links_count;
    *file >> links_count;

    for (std::size_t i = 0; i < links_count; i++) {
        std::size_t pt1, pt2, pt3;
        *file >> pt1 >> pt2 >> pt3;
        builder->build_poly(pt1, pt2, pt3);
    }

    return builder->get();
}

void Load::FileModelLoader::open(std::string &fname) {
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

void Load::FileModelLoader::close() {
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