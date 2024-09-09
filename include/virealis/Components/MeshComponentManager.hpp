#include <virealis/Core/Entity.hpp>
#include <virealis/Math/Vector3.hpp>
#include <virealis/Math/Vector2.hpp>
#include <vector>
#include <unordered_map>

namespace virealis {

class MeshComponentManager {
private:
    struct MeshData {
        std::vector<Entity> entities;
        std::vector<std::vector<Vector3>> vertices;
        std::vector<std::vector<Vector3>> normals;
        std::vector<std::vector<Vector2>> uvCoordinates;  // New vector for UV coordinates
        std::vector<std::vector<uint32_t>> indices;
    };

    MeshData data;
    std::unordered_map<Entity, size_t> entityToIndexMap;

public:
    void create(Entity entity, const std::vector<Vector3>& vertices,
                const std::vector<uint32_t>& indices,
                const std::vector<Vector3>& normals,
                const std::vector<Vector2>& uvCoords = {});
    void destroy(Entity entity);
    std::vector<Vector3> getVertices(Entity entity) const;
    std::vector<Vector3> getNormals(Entity entity) const;
    std::vector<Vector2> getUVCoordinates(Entity entity) const;
    std::vector<uint32_t> getIndices(Entity entity) const;
    bool isValid(Entity entity) const;
};

} // namespace virealis
