//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma onсe

#include <memory>

#include <config/abstract_config.h>

class ConfigurationCreator {
public:
    std::shared_ptr<AbstractConfiguration> get_configuration(std::shared_ptr<std::string> source = nullptr);

private:
    void create_instance(std::shared_ptr<std::string> &source);

    std::shared_ptr<AbstractConfiguration> _conf;
};