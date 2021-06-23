//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

#include <memory>

#include <commands/base_command.h>

class Facade {
public:
    void execute(BaseCommand &cmd);
};
