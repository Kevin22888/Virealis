#include <virealis/Core/EntityManager.hpp>

namespace virealis {

Entity EntityManager::createEntity() {
    uint32_t index;
    if (!freeIndices.empty()) {
        index = freeIndices.front();
        freeIndices.pop();
    } else {
        index = static_cast<uint32_t>(generations.size());
        generations.push_back(0); // start with generation 0
    }
    return { index, generations[index] };
}

void EntityManager::destroyEntity(Entity entity) {
    const uint32_t index = entity.index;
    if (index < generations.size()) {
        generations[index]++;
        freeIndices.push(index);
    }
}

bool EntityManager::isValid(Entity entity) const {
    return entity.index < generations.size() &&
           generations[entity.index] == entity.generation;
}

} // namespace virealis