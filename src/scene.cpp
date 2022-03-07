#include <scene.h>

Scene::Scene() {
    _entityManager = new EntityManager();
    _componentManager = new ComponentManager();
}

Scene::~Scene() {
    delete _entityManager;
    delete _componentManager;
}

Entity Scene::CreateEntity() {
    return _entityManager->CreateEntity();
}

void Scene::DestroyEntity(Entity p_entity) {
    _entityManager->DestroyEntity(p_entity);
}