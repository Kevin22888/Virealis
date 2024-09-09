#include <virealis/Components/MeshComponentManager.hpp>
#include <stdexcept>

namespace virealis {

void MeshComponentManager::create(Entity entity, 
                                  const std::vector<Vector3>& vertices,
                                  const std::vector<uint32_t>& indices,
                                  const std::vector<Vector3>& normals,
                                  const std::vector<Vector2>& uvCoords) {
    if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
        throw std::runtime_error("Entity already has a mesh component.");
    }

    size_t index = data.entities.size();
    data.entities.push_back(entity);
    data.vertices.push_back(vertices);
    data.normals.push_back(normals);
    data.uvCoordinates.push_back(uvCoords);  // Add UV coordinates
    data.indices.push_back(indices);

    entityToIndexMap[entity] = index;
}

void MeshComponentManager::destroy(Entity entity) {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        return; // Entity doesn't have a mesh component
    }

    size_t index = it->second;
    size_t lastIndex = data.entities.size() - 1;

    // Swap with the last element to maintain a compact array
    data.entities[index] = data.entities[lastIndex];
    data.vertices[index] = data.vertices[lastIndex];
    data.normals[index] = data.normals[lastIndex];
    data.indices[index] = data.indices[lastIndex];

    // Update the index map
    entityToIndexMap[data.entities[index]] = index;

    // Remove the last element
    data.entities.pop_back();
    data.vertices.pop_back();
    data.normals.pop_back();
    data.indices.pop_back();
    entityToIndexMap.erase(entity);
}

std::vector<Vector3> MeshComponentManager::getVertices(Entity entity) const {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        throw std::runtime_error("Entity does not have a mesh component.");
    }
    return data.vertices[it->second];
}

std::vector<Vector3> MeshComponentManager::getNormals(Entity entity) const {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        throw std::runtime_error("Entity does not have a mesh component.");
    }
    return data.normals[it->second];
}

std::vector<Vector2> MeshComponentManager::getUVCoordinates(Entity entity) const {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        throw std::runtime_error("Entity does not have a mesh component.");
    }
    return data.uvCoordinates[it->second];
}

std::vector<uint32_t> MeshComponentManager::getIndices(Entity entity) const {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        throw std::runtime_error("Entity does not have a mesh component.");
    }
    return data.indices[it->second];
}

bool MeshComponentManager::isValid(Entity entity) const {
    return entityToIndexMap.find(entity) != entityToIndexMap.end();
}

} // namespace virealis
