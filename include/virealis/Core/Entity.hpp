#ifndef VIREALIS_ENTITY_H
#define VIREALIS_ENTITY_H

#include <cstdint>
#include <functional>

namespace virealis {

struct Entity {
    uint32_t index;
    uint32_t generation;

    bool operator==(const Entity& other) const {
        return index == other.index && generation == other.generation;
    }

    bool operator!=(const Entity& other) const {
        return !(*this == other);
    }
};

} // namespace virealis

// Specialize std::hash for Entity
namespace std {
    template<>
    struct hash<virealis::Entity> {
        std::size_t operator()(const virealis::Entity& entity) const {
            return std::hash<uint32_t>()(entity.index) ^ (std::hash<uint32_t>()(entity.generation) << 1);
        }
    };
}

#endif // VIREALIS_ENTITY_H