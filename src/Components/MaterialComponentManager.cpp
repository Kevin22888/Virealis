#include <virealis/Components/MaterialComponentManager.hpp>
#include <stdexcept>

namespace virealis {

void MaterialComponentManager::create(Entity entity, const Vector3& diffuseColor,
                                      const Vector3& specularColor, float shininess,
                                      const std::string& texture,
                                      float opacity, float reflectivity) {
    if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
        throw std::runtime_error("Entity already has a material component.");
    }

    size_t index = data.entities.size();
    data.entities.push_back(entity);
    data.diffuseColors.push_back(diffuseColor);
    data.specularColors.push_back(specularColor);
    data.shininesses.push_back(shininess);
    data.textures.push_back(texture);  // Optional texture
    data.opacities.push_back(opacity);
    data.reflectivities.push_back(reflectivity);

    entityToIndexMap[entity] = index;
}

void MaterialComponentManager::destroy(Entity entity) {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        return; // Entity doesn't have a material component
    }

    size_t index = it->second;
    size_t lastIndex = data.entities.size() - 1;

    // Swap with the last element to maintain a compact array
    data.entities[index] = data.entities[lastIndex];
    data.diffuseColors[index] = data.diffuseColors[lastIndex];
    data.specularColors[index] = data.specularColors[lastIndex];
    data.shininesses[index] = data.shininesses[lastIndex];
    data.textures[index] = data.textures[lastIndex];
    data.opacities[index] = data.opacities[lastIndex];
    data.reflectivities[index] = data.reflectivities[lastIndex];

    // Update the index map
    entityToIndexMap[data.entities[index]] = index;

    // Remove the last element
    data.entities.pop_back();
    data.diffuseColors.pop_back();
    data.specularColors.pop_back();
    data.shininesses.pop_back();
    data.textures.pop_back();
    data.opacities.pop_back();
    data.reflectivities.pop_back();
    entityToIndexMap.erase(entity);
}

Vector3 MaterialComponentManager::getDiffuseColor(Entity entity) const {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        throw std::runtime_error("Entity does not have a material component.");
    }
    return data.diffuseColors[it->second];
}

Vector3 MaterialComponentManager::getSpecularColor(Entity entity) const {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        throw std::runtime_error("Entity does not have a material component.");
    }
    return data.specularColors[it->second];
}

float MaterialComponentManager::getShininess(Entity entity) const {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        throw std::runtime_error("Entity does not have a material component.");
    }
    return data.shininesses[it->second];
}

std::string MaterialComponentManager::getTexture(Entity entity) const {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        throw std::runtime_error("Entity does not have a material component.");
    }
    return data.textures[it->second];
}

float MaterialComponentManager::getOpacity(Entity entity) const {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        throw std::runtime_error("Entity does not have a material component.");
    }
    return data.opacities[it->second];
}

float MaterialComponentManager::getReflectivity(Entity entity) const {
    auto it = entityToIndexMap.find(entity);
    if (it == entityToIndexMap.end()) {
        throw std::runtime_error("Entity does not have a material component.");
    }
    return data.reflectivities[it->second];
}

bool MaterialComponentManager::isValid(Entity entity) const {
    return entityToIndexMap.find(entity) != entityToIndexMap.end();
}

} // namespace virealis
