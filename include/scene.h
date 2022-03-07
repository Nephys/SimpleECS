#ifndef _SCENE_H_
#define _SCENE_H_

#include <set>

#include <types.h>
#include <entity_manager.h>
#include <component_manager.h>

class Scene {
private:
    EntityManager* _entityManager;
    ComponentManager* _componentManager;
public:
    Scene();
    ~Scene();
    
    Entity CreateEntity();
    void DestroyEntity(Entity p_entity);

    template<typename T>
    inline T* AddComponent(Entity p_entity) {
        _entityManager->AddComponent<T>(p_entity);
        T* component = _componentManager->AddComponent<T>(p_entity);
        return component;
    };

    template<typename T>
    inline T* GetComponent(Entity p_entity) {
        if(!_entityManager->HasComponent<T>(p_entity)) {
            return nullptr;
        }

        T* component = _componentManager->GetComponent<T>(p_entity);
        return component;
    };

    template<typename T>
    inline void RemoveComponent(Entity p_entity) {
        _entityManager->RemoveComponent<T>(p_entity);
    };

    template<typename ... ComponentTypes>
    inline std::set<Entity> Fetch() {
        ComponentType types[] = { Component<ComponentTypes>::Type ... };
        size_t typeCount = sizeof(types) / sizeof(ComponentType);

        Signature systemSignature = Signature();
        for (size_t i = 0; i < typeCount; i++) {
            ComponentType type = types[i];
            systemSignature.set(type);
        }

        return _entityManager->GetEntities(systemSignature);
    };
};

#endif // _SCENE_H_