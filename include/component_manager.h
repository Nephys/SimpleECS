#ifndef _ECS_COPONENT_MANAGER_H_
#define _ECS_COPONENT_MANAGER_H_

#include <iostream>
#include <vector>

#include <types.h>
#include <component.h>
#include <component_pool.h>

class ComponentManager {
private:
    inline static ComponentType _typeCount = 0;
    inline static std::vector<size_t> _componentsRegistry = std::vector<size_t>();
    std::vector<ComponentPool*> _components = std::vector<ComponentPool*>();
public:
    ComponentManager();
    ~ComponentManager();

    template<typename T>
    inline static void RegisterComponent() {
        ComponentType type = Component<T>::Type;
        size_t size = Component<T>::Size;

        printf("Registering component type: %u\n", type);
        
        if(_componentsRegistry.size() <= type) {
            _componentsRegistry.resize(type + 1, 0);
        }
        if(_componentsRegistry[type] != 0) { return; }

        _componentsRegistry[type] = size;
        _typeCount++;
    };
    
    template<typename T>
    inline T* AddComponent(Entity p_entity) {
        ComponentType type = Component<T>::Type;
        if(_typeCount <= type) {
            printf("Unknown component type: %u\n", type);
            abort();
        }

        T* component = new(_components[type]->Get(p_entity)) T();
        return component;
    };

    template<typename T>
    inline T* GetComponent(Entity p_entity) {
        ComponentType type = Component<T>::Type;
        if(_typeCount <= type) {
            printf("Unknown component type: %u\n", type);
            abort();
        }

        T* component = static_cast<T*>(_components[type]->Get(p_entity));
        return component;
    };
};

#endif // _ECS_COPONENT_MANAGER_H_