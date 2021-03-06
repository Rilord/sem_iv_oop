#include <managers/load_manager_creator.h>

std::shared_ptr<Load::LoadManager> Load::LoadManagerCreator::create_manager() {
    if (nullptr == _manager)
        create_instance();

    return _manager;
}

std::shared_ptr<Load::LoadManager> Load::LoadManagerCreator::create_manager(const std::shared_ptr<AbstractLoadController> &loader) {
    if (nullptr == _manager)
        create_instance();

    _manager->set_loader(loader);

    return _manager;
}

void Load::LoadManagerCreator::create_instance() {
    static std::shared_ptr<LoadManager> manager(new LoadManager());

    _manager = manager;
}
