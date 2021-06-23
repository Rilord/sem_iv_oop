//
// Created by Kirill Diordiev on 25.05.2021.
//

#include <facade/facade.h>


void Facade::execute(BaseCommand &cmd) {
    cmd.execute();
}
