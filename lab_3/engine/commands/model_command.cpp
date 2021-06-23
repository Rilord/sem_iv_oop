//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <commands/model_command.h>

#include <load_controller/model_load_controller_creator.h>
#include <managers/load_manager_creator.h>
#include <managers/transform_manager_creator.h>
#include <managers/scene_manager_creator.h>
#include <utility>


MoveModel::MoveModel(const double &dx, const double &dy, const double &dz, const std::size_t &mnumb) : dx(dx), dy(dy), dz(dz), model_numb(mnumb) {}

void MoveModel::execute() {
    Vertex move(dx, dy, dz);
    Vertex scale(1, 1, 1);
    Vertex turn(0, 0, 0);

    std::shared_ptr<Object> model = SceneManagerCreator().create_manager()->get_scene()->get_models().at(model_numb);
    TransformManagerCreator().create_manager()->transform_object(model, move, scale, turn);
}

ScaleModel::ScaleModel(const double &kx, const double &ky, const double &kz, const std::size_t &mnumb) : kx(kx), ky(ky), kz(kz), model_numb(mnumb) {}

void ScaleModel::execute() {
    Vertex move(0, 0, 0);
    Vertex scale(kx, ky, kz);
    Vertex turn(0, 0, 0);

    std::shared_ptr<Object> model = SceneManagerCreator().create_manager()->get_scene()->get_models().at(model_numb);
    TransformManagerCreator().create_manager()->transform_object(model, move, scale, turn);
}

RotateModel::RotateModel(const double &ox, const double &oy, const double &oz, const std::size_t &mnumb) : ox(ox), oy(oy), oz(oz), model_numb(mnumb) {}

void RotateModel::execute() {
    Vertex move(0, 0, 0);
    Vertex scale(1, 1, 1);
    Vertex turn(ox, oy, oz);

    std::shared_ptr<Object> model = SceneManagerCreator().create_manager()->get_scene()->get_models().at(model_numb);
    TransformManagerCreator().create_manager()->transform_object(model, move, scale, turn);
}

transformModel::transformModel(const std::size_t &numb, const Vertex &move, const Vertex &scale, const Vertex &turn) : model_numb(numb), move(move), scale(scale), turn(turn) {}

void transformModel::execute() {
    std::shared_ptr<Object> model = SceneManagerCreator().create_manager()->get_scene()->get_models().at(model_numb);
    TransformManagerCreator().create_manager()->transform_object(model, move, scale, turn);
}

LoadModel::LoadModel(std::string fname) : fname(std::move(fname)) {}

void LoadModel::execute() {
    auto controller = Load::ModelLoadControllerCreator().create_controller();
    auto manager = Load::LoadManagerCreator().create_manager(controller);

    auto model = manager->load(fname);
    SceneManagerCreator().create_manager()->get_scene()->add_model(model);
}

ExportModel::ExportModel(std::string fname) {
}

void ExportModel::execute() {
}

AddModel::AddModel(std::shared_ptr<Object> model) : model(std::move(model)) {}

void AddModel::execute() {
    SceneManagerCreator().create_manager()->get_scene()->add_model(model);
}

RemoveModel::RemoveModel(const std::size_t &model_numb) : model_numb(model_numb) {}

void RemoveModel::execute() {
    SceneManagerCreator().create_manager()->get_scene()->remove_model(model_numb);
}

ModelCount::ModelCount(std::shared_ptr<size_t> &count) : _count(count) {}

void ModelCount::execute() {
    (*_count) = SceneManagerCreator().create_manager()->get_scene()->get_models().size();
}
