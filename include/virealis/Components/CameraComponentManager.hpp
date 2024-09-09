#include <virealis/Core/Entity.hpp>
#include <virealis/Math/Vector3.hpp>
#include <virealis/Math/Matrix4x4.hpp>
#include <vector>
#include <unordered_map>

namespace virealis {

class CameraComponentManager {
public:
    enum class ProjectionType { Perspective, Orthographic };

private:
    struct CameraData {
        std::vector<Entity> entities;
        std::vector<Vector3> positions;
        std::vector<Vector3> orientations;  // Could also be a quaternion
        std::vector<Matrix4x4> viewMatrices;
        std::vector<Matrix4x4> projectionMatrices;
        std::vector<float> fovs; // Field of View for perspective projection
        std::vector<float> aspectRatios;
        std::vector<float> nearPlanes;
        std::vector<float> farPlanes;
        std::vector<ProjectionType> projectionTypes;
    };

    CameraData data;
    std::unordered_map<Entity, size_t> entityToIndexMap;

public:
    void create(Entity entity, const Vector3& position, const Vector3& orientation,
                ProjectionType projectionType, float fov, float aspectRatio,
                float nearPlane, float farPlane);

    void destroy(Entity entity);
    Matrix4x4 getViewMatrix(Entity entity) const;
    Matrix4x4 getProjectionMatrix(Entity entity) const;
    void updateCamera(Entity entity, const Vector3& position, const Vector3& orientation);
    bool isValid(Entity entity) const;
};

} // namespace virealis
