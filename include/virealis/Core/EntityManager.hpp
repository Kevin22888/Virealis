#ifndef VIREALIS_ENTITY_MANAGER_H
#define VIREALIS_ENTITY_MANAGER_H

#include <virealis/Core/Entity.hpp>
#include <vector>
#include <queue>
#include <cstdint>

namespace virealis {

class EntityManager {
private:
    std::vector<uint32_t> generations;
    std::queue<uint32_t> freeIndices;

public:
    EntityManager() = default;
    ~EntityManager() = default;

    Entity createEntity();
    void destroyEntity(Entity entity);
    bool isValid(Entity entity) const;
};

} // namespace virealis

#endif // VIREALIS_ENTITY_MANAGER_H