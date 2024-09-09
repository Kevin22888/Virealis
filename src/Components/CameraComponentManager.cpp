#include <virealis/Components/CameraComponentManager.hpp>
#include <virealis/Math/Matrix4x4.hpp>
#include <stdexcept>

namespace virealis {

void CameraComponentManager::create(Entity entity, const Vector3& position,
                                    const Vector3& orientation,
                                    ProjectionType projectionType, float fov,
                                    float aspectRatio, float nearPlane,
                                    float farPlane) {
    if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
        throw std::runtime_error("Entity already has a camera component.");
    }

    size_t index = data.entities.size();
    data.entities.push_back(entity);
    data.positions.push_back(position);
    data.orientations.push_back(orientation);
    data.fovs.push_back(fov);
    data.aspectRatios.push_back(aspectRatio);
    data.nearPlanes.push_back(nearPlane);
    data.farPlanes.push_back(farPlane);
    data.projectionTypes.push_back(projectionType);

    // Calculate the initial view and projection matrices
    Matrix4x4 viewMatrix = Matrix4x4::lookAt(position, position + orientation, Vector3(0, 1, 0));
    Matrix4x4 projectionMatrix = (projectionType == ProjectionType::Perspective)
                                     ? Matrix4x4::perspective(fov, aspectRatio, nearPlane, farPlane)
                                     : Matrix4x4::orthographic(-aspectRatio, aspectRatio, -1.0f, 1.0f, nearPlane, farPlane);

    data.viewMatrices.push_back(viewMatrix);
    data.projectionMatrices.push_back(projectionMatrix);

    entityToIndexMap[entity] = index;
}

void CameraComponentManager::destroy(Entity entity) {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        return; // Entity doesn't have a camera component
    }

    size_t index = it->second;
    size_t lastIndex = data.entities.size() - 1;

    // Swap with the last element to maintain a compact array
    data.entities[index] = data.entities[lastIndex];
    data.positions[index] = data.positions[lastIndex];
    data.orientations[index] = data.orientations[lastIndex];
    data.viewMatrices[index] = data.viewMatrices[lastIndex];
    data.projectionMatrices[index] = data.projectionMatrices[lastIndex];
    data.fovs[index] = data.fovs[lastIndex];
    data.aspectRatios[index] = data.aspectRatios[lastIndex];
    data.nearPlanes[index] = data.nearPlanes[lastIndex];
    data.farPlanes[index] = data.farPlanes[lastIndex];
    data.projectionTypes[index] = data.projectionTypes[lastIndex];

    // Update the index map
    entityToIndexMap[data.entities[index]] = index;

    // Remove the last element
    data.entities.pop_back();
    data.positions.pop_back();
    data.orientations.pop_back();
    data.viewMatrices.pop_back();
    data.projectionMatrices.pop_back();
    data.fovs.pop_back();
    data.aspectRatios.pop_back();
    data.nearPlanes.pop_back();
    data.farPlanes.pop_back();
    data.projectionTypes.pop_back();
    entityToIndexMap.erase(entity);
}

Matrix4x4 CameraComponentManager::getViewMatrix(Entity entity) const {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        throw std::runtime_error("Entity does not have a camera component.");
    }
    return data.viewMatrices[it->second];
}

Matrix4x4 CameraComponentManager::getProjectionMatrix(Entity entity) const {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        throw std::runtime_error("Entity does not have a camera component.");
    }
    return data.projectionMatrices[it->second];
}

void CameraComponentManager::updateCamera(Entity entity, const Vector3& position, const Vector3& orientation) {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        throw std::runtime_error("Entity does not have a camera component.");
    }

    size_t index = it->second;
    data.positions[index] = position;
    data.orientations[index] = orientation;

    data.viewMatrices[index] = Matrix4x4::lookAt(position, position + orientation, Vector3(0, 1, 0));
}

bool CameraComponentManager::isValid(Entity entity) const {
    return entityToIndexMap.find(entity) != entityToIndexMap.end();
}

} // namespace virealis
