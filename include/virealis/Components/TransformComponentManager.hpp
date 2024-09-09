#ifndef VIREALIS_TRANSFORM_COMPONENT_MANAGER_H
#define VIREALIS_TRANSFORM_COMPONENT_MANAGER_H

#include <virealis/Core/Entity.hpp>
#include <virealis/Math/Matrix4x4.hpp>
#include <vector>
#include <unordered_map>
#include <cstddef>

namespace virealis {

class TransformComponentManager {
private:
    struct TransformData {
        std::vector<Entity> entities;
        std::vector<Matrix4x4> localTransforms;
        std::vector<Matrix4x4> worldTransforms;
        std::vector<size_t> parents;
        std::vector<size_t> firstChildren;
        std::vector<size_t> nextSiblings;
    };

    TransformData data;
    std::unordered_map<Entity, size_t> entityToIndexMap;

public:
    void create(Entity entity, const Matrix4x4& localTransform);
    void destroy(Entity entity);
    Matrix4x4 getWorldTransform(Entity entity) const;
    void setLocalTransform(Entity entity, const Matrix4x4& localTransform);
    void updateTransforms();
    void setParent(Entity child, Entity parent);
    bool isValid(Entity entity) const;
};

} // namespace virealis

#endif // VIREALIS_TRANSFORM_COMPONENT_MANAGER_H