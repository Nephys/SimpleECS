#include <entity_manager.h>

Entity EntityManager::CreateEntity() {
    if(_entityCount >= MAX_ENTITIES) {
        printf("Too many entities: %u\n", _entityCount);
        abort();
    }
    
    _signatures[_entityCount].reset();
    return _entityCount++;
}

void EntityManager::DestroyEntity(Entity p_entity) {
    if(p_entity >= _entityCount) {
        printf("Entity out of range: %u\n", p_entity);
        abort();
    }

    _signatures[p_entity].reset();
    _entityCount--;
}

Signature EntityManager::GetSignature(Entity p_entity) {
    if(p_entity >= _entityCount) {
        printf("Entity out of range: %u\n", p_entity);
        abort();
    }

    return _signatures[p_entity];
}

std::set<Entity> EntityManager::GetEntities() {
    std::set<Entity> entities = std::set<Entity>();
    for (Entity entity = 0; entity < _entityCount; entity++) {
        entities.insert(entity);
    }
    return entities;
}

std::set<Entity> EntityManager::GetEntities(Signature p_signature) {
    std::set<Entity> entities = std::set<Entity>();
    for (Entity entity = 0; entity < _entityCount; entity++) {
        if((_signatures[entity] & p_signature) == p_signature) {
            entities.insert(entity);
        }
    }
    return entities;
}