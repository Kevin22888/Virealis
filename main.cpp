#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <virealis/Scene/Scene.hpp>
#include <virealis/Rendering/Shader.hpp>
#include <virealis/Systems/RenderingSystem.hpp>
#include <virealis/Math/Matrix4x4.hpp>
#include <virealis/Math/Constants.hpp>


void generateSphereData(int latitudeSegments, int longitudeSegments, std::vector<virealis::Vector3>& vertices, std::vector<uint32_t>& indices) {
    for (int lat = 0; lat <= latitudeSegments; ++lat) {
        float theta = lat * virealis::Constants::PI / latitudeSegments;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);

        for (int lon = 0; lon <= longitudeSegments; ++lon) {
            float phi = lon * 2 * virealis::Constants::PI / longitudeSegments;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            float x = cosPhi * sinTheta;
            float y = cosTheta;
            float z = sinPhi * sinTheta;
            vertices.push_back({x, y, z});
        }
    }

    for (int lat = 0; lat < latitudeSegments; ++lat) {
        for (int lon = 0; lon < longitudeSegments; ++lon) {
            uint32_t first = lat * (longitudeSegments + 1) + lon;
            uint32_t second = first + longitudeSegments + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
}

void GLAPIENTRY MessageCallback( GLenum source,
                                 GLenum type,
                                 GLuint id,
                                 GLenum severity,
                                 GLsizei length,
                                 const GLchar* message,
                                 const void* userParam )
{
    std::cerr << "GL CALLBACK: " << ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ) <<
                 " type = 0x" << std::hex << type <<
                 ", severity = 0x" << severity <<
                 ", message = " << message << std::endl;
}

/*
int main() {
        // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Test", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load OpenGL function pointers using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Now that we have a valid OpenGL context, we can call OpenGL functions
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    // Clean up and close the program
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
*/

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    std::cout << "GLFW Initialized" << std::endl;

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Virealis Engine", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << "Window Created" << std::endl;

    // Set viewport size to match the window dimensions
    // int width, height;
    // glfwGetFramebufferSize(window, &width, &height);
    // glViewport(0, 0, width, height);
    // std::cout << "Set viewport" << std::endl;

    // Make the window's context current
    glfwMakeContextCurrent(window);
    std::cout << "Context Made Current" << std::endl;

    // Load OpenGL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    std::cout << "GLAD Initialized" << std::endl;

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    std::cout << "Depth testing enabled" << std::endl;

    // enabling OpenGL debugging callback
    // glEnable(GL_DEBUG_OUTPUT);
    // std::cout << "Enabled OpenGL Debugging" << std::endl;
    // glDebugMessageCallback(MessageCallback, 0);
    // std::cout << "Set OpenGL Debugging Callback" << std::endl;

    // Create and compile the shaders
    std::string vertexShaderSource = R"(
    #version 120
    attribute vec3 aPosition;
    uniform mat4 uMVP;
    void main() {
        gl_Position = uMVP * vec4(aPosition, 1.0);
    })";
    std::cout << "Vertex Shader Source Created" << std::endl;

    std::string fragmentShaderSource = R"(
    #version 120
    uniform vec3 uDiffuseColor;
    void main() {
        gl_FragColor = vec4(uDiffuseColor, 1.0);
    })";
    std::cout << "Fragment Shader Source Created" << std::endl;

    // Create shader program
    GLuint shaderProgram = virealis::Shader::createShaderProgram(vertexShaderSource, fragmentShaderSource);
    std::cout << "Shader Program Created" << std::endl;

    // Create a scene
    virealis::Scene scene;
    std::cout << "Scene Created" << std::endl;

    // Cube data
    std::vector<virealis::Vector3> cubeVertices = {
        {-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f,  0.5f, -0.5f}, {-0.5f,  0.5f, -0.5f}, // Back face
        {-0.5f, -0.5f,  0.5f}, {0.5f, -0.5f,  0.5f}, {0.5f,  0.5f,  0.5f}, {-0.5f,  0.5f,  0.5f}, // Front face
    };

    std::vector<uint32_t> cubeIndices = {
        0, 1, 2, 2, 3, 0, // Back face
        4, 5, 6, 6, 7, 4, // Front face
        0, 4, 7, 7, 3, 0, // Left face
        1, 5, 6, 6, 2, 1, // Right face
        0, 1, 5, 5, 4, 0, // Bottom face
        3, 2, 6, 6, 7, 3  // Top face
    };

    // Create cube entity
    virealis::Entity cubeEntity = scene.createEntity();
    std::cout << "Cube Entity Created" << std::endl;
    scene.getMeshManager().create(cubeEntity, cubeVertices, cubeIndices, {});
    std::cout << "Cube Mesh Created" << std::endl;
    scene.getMaterialManager().create(cubeEntity, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, 32.0f);  // Red diffuse color
    std::cout << "Cube Material Created" << std::endl;
    scene.getTransformManager().create(cubeEntity, virealis::Matrix4x4::identity());
    std::cout << "Cube Transform Created" << std::endl;

    // Sphere data
    std::vector<virealis::Vector3> sphereVertices;
    std::vector<uint32_t> sphereIndices;
    generateSphereData(16, 16, sphereVertices, sphereIndices);
    std::cout << "Sphere Data Generated" << std::endl;

    // Create sphere entity
    virealis::Entity sphereEntity = scene.createEntity();
    std::cout << "Sphere Entity Created" << std::endl;
    scene.getMeshManager().create(sphereEntity, sphereVertices, sphereIndices, {});
    std::cout << "Sphere Mesh Created" << std::endl;
    scene.getMaterialManager().create(sphereEntity, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, 32.0f);  // Blue diffuse color
    std::cout << "Sphere Material Created" << std::endl;
    scene.getTransformManager().create(sphereEntity, virealis::Matrix4x4::identity());
    std::cout << "Sphere Transform Created" << std::endl;

    // Create a camera entity
    virealis::Entity cameraEntity = scene.createEntity();
    std::cout << "Camera Entity Created" << std::endl;
    scene.getCameraManager().create(cameraEntity, {0.0f, 0.0f, 3.0f}, {0.0f, 0.0f, -1.0f}, 
                                    virealis::CameraComponentManager::ProjectionType::Perspective, 
                                    45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    std::cout << "Camera Created" << std::endl;

    // Create a rendering system
    virealis::RenderingSystem renderingSystem(shaderProgram);
    std::cout << "Rendering System Created" << std::endl;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        std::cout << "Rendering Loop Start" << std::endl;

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        std::cout << "Screen Cleared" << std::endl;

        // Render the scene using the ECS rendering system
        renderingSystem.render(scene, cameraEntity);
        std::cout << "Rendered Scene" << std::endl;

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up
    glDeleteProgram(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
    std::cout << "Clean up completed" << std::endl;

    return 0;
}
