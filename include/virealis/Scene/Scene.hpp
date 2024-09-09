#ifndef VIREALIS_SCENE_H
#define VIREALIS_SCENE_H

#include <virealis/Core/Entity.hpp>
#include <virealis/Components/MeshComponentManager.hpp>
#include <virealis/Components/MaterialComponentManager.hpp>
#include <virealis/Components/TransformComponentManager.hpp>
#include <virealis/Components/CameraComponentManager.hpp>
#include <vector>

namespace virealis {

class Scene {
private:
    std::vector<Entity> entities;
    MeshComponentManager meshManager;
    MaterialComponentManager materialManager;
    TransformComponentManager transformManager;
    CameraComponentManager cameraManager;

public:
    Scene() = default;
    ~Scene() = default;

    // Entity management
    Entity createEntity();
    void destroyEntity(Entity entity);

    // Access component managers
    // Non-const versions (used when you want to modify the scene)
    MeshComponentManager& getMeshManager();
    MaterialComponentManager& getMaterialManager();
    TransformComponentManager& getTransformManager();
    CameraComponentManager& getCameraManager();

    // Const versions (used when you want to read from the scene)
    const MeshComponentManager& getMeshManager() const;
    const MaterialComponentManager& getMaterialManager() const;
    const TransformComponentManager& getTransformManager() const;
    const CameraComponentManager& getCameraManager() const;

    const std::vector<Entity>& getEntities() const;

    // Scene serialization (to be implemented later)
};

} // namespace virealis

#endif // VIREALIS_SCENE_H
