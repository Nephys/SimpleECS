#include <component_manager.h>

ComponentManager::ComponentManager() {
    for (size_t i = 0; i < _componentsRegistry.size(); i++) {
        size_t componentSize = _componentsRegistry[i];
        _components.push_back(new ComponentPool(componentSize));
    }
}

ComponentManager::~ComponentManager() {
    for(ComponentPool* pool : _components) {
        delete pool;
    }
    _components.clear();
}