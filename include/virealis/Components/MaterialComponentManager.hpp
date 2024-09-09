#include <virealis/Core/Entity.hpp>
#include <virealis/Math/Vector3.hpp>
#include <vector>
#include <unordered_map>
#include <string>

namespace virealis {

class MaterialComponentManager {
private:
    struct MaterialData {
        std::vector<Entity> entities;
        std::vector<Vector3> diffuseColors;
        std::vector<Vector3> specularColors;
        std::vector<float> shininesses;
        std::vector<std::string> textures; // Optional texture path
        std::vector<float> opacities;
        std::vector<float> reflectivities;
    };

    MaterialData data;
    std::unordered_map<Entity, size_t> entityToIndexMap;

public:
    void create(Entity entity, const Vector3& diffuseColor,
                const Vector3& specularColor, float shininess,
                const std::string& texture = "", // Optional texture
                float opacity = 1.0f, float reflectivity = 0.0f);
    void destroy(Entity entity);
    Vector3 getDiffuseColor(Entity entity) const;
    Vector3 getSpecularColor(Entity entity) const;
    float getShininess(Entity entity) const;
    std::string getTexture(Entity entity) const;
    float getOpacity(Entity entity) const;
    float getReflectivity(Entity entity) const;
    bool isValid(Entity entity) const;
};

} // namespace virealis
