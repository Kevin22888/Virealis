#ifndef VIREALIS_SHADER_H
#define VIREALIS_SHADER_H

#include <glad/glad.h>
#include <string>

namespace virealis {

class Shader {
public:
    static GLuint loadShader(GLenum type, const std::string& shaderSource);
    static GLuint createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
};

} // namespace virealis

#endif // VIREALIS_SHADER_H
