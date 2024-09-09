#include <virealis/Rendering/Shader.hpp>
#include <iostream>

namespace virealis {

GLuint Shader::loadShader(GLenum type, const std::string& shaderSource) {
    std::cout << "Compiling Shader..." << std::endl;
    GLuint shader = glCreateShader(type);
    const char* src = shaderSource.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    // Check for compilation errors
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Error: Shader Compilation Failed\n" << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Shader Compiled Successfully" << std::endl;
    return shader;
}


GLuint Shader::createShaderProgram(const std::string& vertexSource, const std::string& fragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);

    // Link shaders to create a shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Error: Shader Program Linking Failed\n" << infoLog << std::endl;
        exit(EXIT_FAILURE); // Exit if shader linking fails
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

} // namespace virealis
