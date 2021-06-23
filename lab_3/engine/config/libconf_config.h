//
// Created by Kirill Diordiev on 25.05.2021.
//
#pragma o#include <iostream>nce

#include <memory>

#include <libconfig.h++>

#include <renderer/abstract_renderer.h>

#include <config/abstract_config.h>

#define DEFAULT_FILE "./engine.config"

class LibconfConfiguration : public AbstractConfiguration {
public:
    explicit LibconfConfiguration(std::shared_ptr<std::string> &source);

    void read_configuration(std::shared_ptr<std::string> source = nullptr) override;

    AbstractConfiguration::frames get_frame() override;

    AbstractConfiguration::sources get_load_source() override;

private:

    std::shared_ptr<libconfig::Config> cfg;
};
