//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <config/config_creator.h>

#include <config/libconf_config.h>

std::shared_ptr<AbstractConfiguration> ConfigurationCreator::get_configuration(std::shared_ptr<std::string> source) {
    if (nullptr == _conf)
        create_instance(source);
    else if (source)
        _conf->read_configuration(source);

    return _conf;
}

void ConfigurationCreator::create_instance(std::shared_ptr<std::string> &source) {
    static std::shared_ptr<AbstractConfiguration> conf(new LibconfConfiguration(source));

    _conf = conf;
}