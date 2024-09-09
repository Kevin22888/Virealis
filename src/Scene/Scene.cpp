#include <virealis/Scene/Scene.hpp>
#include <stdexcept>

namespace virealis {

Entity Scene::createEntity() {
    Entity entity = { static_cast<uint32_t>(entities.size()), 0 };
    entities.push_back(entity);
    return entity;
}

void Scene::destroyEntity(Entity entity) {
    auto it = std::find(entities.begin(), entities.end(), entity);
    if (it != entities.end()) {
        entities.erase(it);

        // Destroy components associated with this entity
        meshManager.destroy(entity);
        materialManager.destroy(entity);
        transformManager.destroy(entity);
        cameraManager.destroy(entity);
    }
}

MeshComponentManager& Scene::getMeshManager() {
    return meshManager;
}

const MeshComponentManager& Scene::getMeshManager() const {
    return meshManager;
}

MaterialComponentManager& Scene::getMaterialManager() {
    return materialManager;
}

const MaterialComponentManager& Scene::getMaterialManager() const {
    return materialManager;
}

TransformComponentManager& Scene::getTransformManager() {
    return transformManager;
}

const TransformComponentManager& Scene::getTransformManager() const {
    return transformManager;
}

CameraComponentManager& Scene::getCameraManager() {
    return cameraManager;
}

const CameraComponentManager& Scene::getCameraManager() const {
    return cameraManager;
}

const std::vector<Entity>& Scene::getEntities() const {
    return entities;
}

} // namespace virealis
