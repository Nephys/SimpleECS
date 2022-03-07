#ifndef _ECS_COMPONENT_POOL_H_
#define _ECS_COMPONENT_POOL_H_

#include <types.h>

class ComponentPool {
private:
    char* _data;
    size_t _size;
public:
    ComponentPool(size_t p_size);
    ~ComponentPool();

    void* Get(Entity p_entity);
};

#endif // _ECS_COMPONENT_POOL_H_