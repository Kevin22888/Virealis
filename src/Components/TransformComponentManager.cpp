#include <virealis/Components/TransformComponentManager.hpp>
#include <stdexcept>

namespace virealis {

void TransformComponentManager::create(Entity entity, const Matrix4x4& localTransform) {
    size_t index = data.entities.size();

    data.entities.push_back(entity);
    data.localTransforms.push_back(localTransform);
    data.worldTransforms.push_back(Matrix4x4::identity()); // Initialize with identity matrix
    data.parents.push_back(std::numeric_limits<size_t>::max()); // No parent initially
    data.firstChildren.push_back(std::numeric_limits<size_t>::max()); // No children initially
    data.nextSiblings.push_back(std::numeric_limits<size_t>::max()); // No siblings initially

    entityToIndexMap[entity] = index;
}

void TransformComponentManager::destroy(Entity entity) {
    auto it = entityToIndexMap.find(entity);
    if (it != entityToIndexMap.end()) {
        size_t index = it->second;
        size_t lastIndex = data.entities.size() - 1;

        // Move last element to the current index
        data.entities[index] = data.entities[lastIndex];
        data.localTransforms[index] = data.localTransforms[lastIndex];
        data.worldTransforms[index] = data.worldTransforms[lastIndex];
        data.parents[index] = data.parents[lastIndex];
        data.firstChildren[index] = data.firstChildren[lastIndex];
        data.nextSiblings[index] = data.nextSiblings[lastIndex];

        // Update the map with the new index
        entityToIndexMap[data.entities[index]] = index;

        // Remove the last element
        data.entities.pop_back();
        data.localTransforms.pop_back();
        data.worldTransforms.pop_back();
        data.parents.pop_back();
        data.firstChildren.pop_back();
        data.nextSiblings.pop_back();

        // Remove the entity from the map
        entityToIndexMap.erase(it);
    }
}

Matrix4x4 TransformComponentManager::getWorldTransform(Entity entity) const {
    auto it = entityToIndexMap.find(entity);
    if (it != entityToIndexMap.end()) {
        return data.worldTransforms[it->second];
    }
    throw std::runtime_error("Entity not found in TransformComponentManager.");
}

void TransformComponentManager::setLocalTransform(Entity entity, const Matrix4x4& localTransform) {
    auto it = entityToIndexMap.find(entity);
    if (it != entityToIndexMap.end()) {
        data.localTransforms[it->second] = localTransform;
    } else {
        throw std::runtime_error("Entity not found in TransformComponentManager.");
    }
}

void TransformComponentManager::updateTransforms() {
    for (size_t i = 0; i < data.entities.size(); ++i) {
        size_t parentIndex = data.parents[i];
        if (parentIndex != std::numeric_limits<size_t>::max()) {
            data.worldTransforms[i] = data.localTransforms[i] * data.worldTransforms[parentIndex];
        } else {
            data.worldTransforms[i] = data.localTransforms[i];
        }

        // Update children recursively (could be improved with a non-recursive implementation)
        size_t childIndex = data.firstChildren[i];
        while (childIndex != std::numeric_limits<size_t>::max()) {
            data.worldTransforms[childIndex] = data.localTransforms[childIndex] * data.worldTransforms[i];
            childIndex = data.nextSiblings[childIndex];
        }
    }
}

void TransformComponentManager::setParent(Entity child, Entity parent) {
    size_t childIndex = entityToIndexMap[child];
    size_t parentIndex = entityToIndexMap[parent];

    // Set the parent of the child
    data.parents[childIndex] = parentIndex;

    // Link the child into the parent's children list
    if (data.firstChildren[parentIndex] == std::numeric_limits<size_t>::max()) {
        // If the parent has no children, this child becomes the first child
        data.firstChildren[parentIndex] = childIndex;
    } else {
        // Otherwise, find the last sibling and link this child after it
        size_t siblingIndex = data.firstChildren[parentIndex];
        while (data.nextSiblings[siblingIndex] != std::numeric_limits<size_t>::max()) {
            siblingIndex = data.nextSiblings[siblingIndex];
        }
        data.nextSiblings[siblingIndex] = childIndex;
    }

    // Initialize the child's next sibling as invalid
    data.nextSiblings[childIndex] = std::numeric_limits<size_t>::max();
}

bool TransformComponentManager::isValid(Entity entity) const {
    return entityToIndexMap.find(entity) != entityToIndexMap.end();
}

}

/*
We are using a Structure of Arrays (SoA) layout for the data.
We also keep all data tightly packed to further improve memory.

create:
Assign a new transform component to the input entity, and use the input local transform matrix
to record this component's position in the world (world transform is set to identity initially).
Because we keep data tightly packed, the entity's index is not the actual index to get its component,
instead we have a map from an entity struct to the index that retrieves the component data.
*/
