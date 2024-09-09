#include <virealis/Systems/RenderingSystem.hpp>
#include <iostream> // For debug logging

namespace virealis {

void RenderingSystem::render(const Scene& scene, Entity activeCameraEntity) {
    // Get the camera component manager and retrieve the view/projection matrices
    const CameraComponentManager& cameraManager = scene.getCameraManager();
    const MeshComponentManager& meshManager = scene.getMeshManager();
    const MaterialComponentManager& materialManager = scene.getMaterialManager();
    const TransformComponentManager& transformManager = scene.getTransformManager();

    Matrix4x4 viewMatrix = cameraManager.getViewMatrix(activeCameraEntity);
    Matrix4x4 projectionMatrix = cameraManager.getProjectionMatrix(activeCameraEntity);

    // Use the shader program
    glUseProgram(shaderProgram);

    // For each entity in the scene that has a mesh
    for (const Entity& entity : scene.getEntities()) {
        // Check if the entity has the necessary components
        if (!meshManager.isValid(entity) || !transformManager.isValid(entity) || !materialManager.isValid(entity)) {
            continue; // Skip if entity doesn't have required components
        }

        // Get the mesh data (vertices, indices)
        auto vertices = meshManager.getVertices(entity);
        auto indices = meshManager.getIndices(entity);

        // Get the material data (diffuse color)
        Vector3 diffuseColor = materialManager.getDiffuseColor(entity);

        // Get the transform data (model matrix)
        Matrix4x4 modelMatrix = transformManager.getWorldTransform(entity);

        // Set shader uniforms (MVP matrix, diffuse color)
        Matrix4x4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uMVP"), 1, GL_FALSE, mvpMatrix.data());
        glUniform3fv(glGetUniformLocation(shaderProgram, "uDiffuseColor"), 1, &diffuseColor.x);

        // Set up vertex buffers (VBOs) and index buffers (EBOs) for the mesh
        GLuint vao, vbo, ebo;
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        glBindVertexArray(vao);

        // Upload vertex data
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), vertices.data(), GL_STATIC_DRAW);

        // Upload index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

        // Set vertex attribute pointers (for position)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), (void*)0);  // Position attribute
        glEnableVertexAttribArray(0);

        // Draw the object
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        // Clean up
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
    }

    // Unbind the shader program
    glUseProgram(0);
}

} // namespace virealis
