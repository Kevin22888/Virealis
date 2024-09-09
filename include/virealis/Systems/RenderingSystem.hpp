#ifndef VIREALIS_RENDERING_SYSTEM_H
#define VIREALIS_RENDERING_SYSTEM_H

#include <virealis/Scene/Scene.hpp>
#include <glad/glad.h>   // OpenGL function loader
#include <GLFW/glfw3.h>  // For GLFW context management (if needed for windowing)

namespace virealis {

class RenderingSystem {
private:
    GLuint shaderProgram;

public:
    // Constructor initializes with a compiled shader program
    RenderingSystem(GLuint shaderProgram);
    
    // Render function that takes a scene and the active camera entity
    void render(const Scene& scene, Entity activeCameraEntity);
};

} // namespace virealis

#endif // VIREALIS_RENDERING_SYSTEM_H
