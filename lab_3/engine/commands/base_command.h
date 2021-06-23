//
// Created by Kirill Diordiev on 25.05.2021.
//

#pragma once

class BaseCommand {
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;
    virtual void execute() = 0;
};
