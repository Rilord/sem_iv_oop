//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once


#include <memory>
#include <string>

#include <commands/base_command.h>
#include <renderer/abstract_renderer.h>


class SceneBaseCommand : public BaseCommand {};


class RenderScene : public SceneBaseCommand {
public:
    RenderScene() = delete;
    explicit RenderScene(std::shared_ptr<AbstractRenderer> Renderer);
    ~RenderScene() override = default;

    void execute() override;

private:
    std::shared_ptr<AbstractRenderer> _Renderer;
};

class LoadScene : public SceneBaseCommand {
public:
    LoadScene() = delete;
    explicit LoadScene(std::string fname);
    ~LoadScene() override = default;

    void execute() override;

private:
    std::string _fname;
};