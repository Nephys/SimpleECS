#ifndef _ECS_ENTITY_MANAGER_H_
#define _ECS_ENTITY_MANAGER_H_

#include <array>
#include <set>

#include <types.h>
#include <component.h>

class EntityManager {
private:
    std::array<Signature, MAX_ENTITIES> _signatures = std::array<Signature, MAX_ENTITIES>();

    Entity _entityCount;
public:
    EntityManager() = default;
    ~EntityManager() = default;

    Entity CreateEntity();
    void DestroyEntity(Entity p_entity);

    Signature GetSignature(Entity p_entity);
    std::set<Entity> GetEntities();
    std::set<Entity> GetEntities(Signature p_signature);

    template<typename T>
    inline bool HasComponent(Entity p_entity) {
        if(p_entity >= _entityCount) {
            printf("Entity out of range: %u\n", p_entity);
            abort();
        }
        
        ComponentType type = Component<T>::Type;
        return _signatures[p_entity].test(type);
    };

    template<typename T>
    inline void AddComponent(Entity p_entity) {
        if(p_entity >= _entityCount) {
            printf("Entity out of range: %u\n", p_entity);
            abort();
        }

        ComponentType type = Component<T>::Type;
        _signatures[p_entity].set(type);
    };

    template<typename T>
    inline void RemoveComponent(Entity p_entity) {
        if(p_entity >= _entityCount) {
            printf("Entity out of range: %u\n", p_entity);
            abort();
        }

        ComponentType type = Component<T>::Type;
        _signatures[p_entity].reset(type);
    };
};


#endif // _ECS_ENTITY_MANAGER_H_