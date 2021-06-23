//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <memory>
#include <utility>

#include <managers/render_manager.h>

#include <objects/model/mesh.h>
#include <objects/model/edge.h>
#include <objects/model/vertex.h>
#include <objects/object.h>

class Model : public VisibleObject {
    friend void RenderManager::spectate(const Model &model);

public:
    Model() : _details(new ModelDetails){};
    explicit Model(std::shared_ptr<ModelDetails> details) : _details(std::move(details)){};
    Model(const Model &model);
    ~Model() override = default;

    void transform(const Vertex &move, const Vertex &scale, const Vertex &rotate) override;
    void accept(std::shared_ptr<Spectator> visitor) override;

protected:
    std::shared_ptr<ModelDetails> _details;
};