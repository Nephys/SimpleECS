#include <component_pool.h>

ComponentPool::ComponentPool(size_t p_size) {
    _size = p_size;
    _data = new char[_size * MAX_ENTITIES];
}

ComponentPool::~ComponentPool() {
    delete[] _data;
}

void* ComponentPool::Get(Entity p_entity) {
    return _data + _size * p_entity;
}