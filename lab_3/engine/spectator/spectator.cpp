//
// Created by Kirill Diordiev on 09.06.2021.
//

#include <spectator/spectator.h>
#include <objects/model/model.h>
#include <objects/camera/camera.h>

Spectator::Spectator(const std::shared_ptr<Camera> &_camera, const std::shared_ptr<AbstractRenderer> _renderer)
        :_camera(_camera), _renderer(_renderer)
{
}

void Spectator::spectate_model(Model &_model)
{
    auto details = _model._details;
    auto Vertexs = details->get_Vertexs();
    auto edges = details->get_edges();

    for (auto &edge : edges)
    {
        _renderer->render_line(get_projection(Vertexs[edge.get_fst()]),
                           get_projection(Vertexs[edge.get_snd()]));
    }
}

Vertex Spectator::get_projection(Vertex &_Vertex)
{
    Vertex projection(_Vertex);
    Vertex move(-_camera->getX(), -_camera->getY(), 0);
    std::shared_ptr<Matrix<double>> reform_mtr(std::make_shared<MoveMatrix>(_camera->get_position()));

    projection.rotate(reform_mtr);

    Vertex angles = _camera().deg_to_rad();
    reform_mtr = std::make_shared<RotateOxMatrix>(-angles.get_x());
    projection.reform(reform_mtr);

    reform_mtr = std::make_shared<RotateOyMatrix>(-angles.get_y());
    projection.reform(reform_mtr);

    reform_mtr = std::make_shared<RotateOzMatrix>(-angles.get_z());
    projection.reform(reform_mtr);

    return projection;
}