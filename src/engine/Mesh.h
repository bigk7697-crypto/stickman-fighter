#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace Engine {

// Structure d'un vertex simple
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Color;
    glm::vec2 TexCoord;  // Pour plus tard (textures)
    glm::vec3 Normal;    // Pour plus tard (lumière)
    
    Vertex() = default;
    Vertex(const glm::vec3& pos, const glm::vec3& col) 
        : Position(pos), Color(col), TexCoord(0.0f), Normal(0.0f) {}
    Vertex(const glm::vec3& pos, const glm::vec3& col, const glm::vec2& tex, const glm::vec3& norm)
        : Position(pos), Color(col), TexCoord(tex), Normal(norm) {}
};

class Mesh {
public:
    Mesh();
    ~Mesh();

    // Créer depuis des données brutes
    void SetVertices(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);
    
    // Primitives prédéfinies
    static Mesh CreateTriangle(const glm::vec3& color = glm::vec3(1.0f));
    static Mesh CreateCube(float size = 1.0f);
    static Mesh CreateQuad(float size = 1.0f);

    void Bind() const;
    void Unbind() const;
    void Draw() const;

    // Modification dynamique (pour animation)
    void UpdateVertices(const std::vector<Vertex>& vertices);

    bool IsValid() const { return m_VAO != 0; }

private:
    GLuint m_VAO = 0;  // Vertex Array Object
    GLuint m_VBO = 0;  // Vertex Buffer Object
    GLuint m_EBO = 0;  // Element Buffer Object (indices)
    
    GLsizei m_IndexCount = 0;
    GLsizei m_VertexCount = 0;
    bool m_HasIndices = false;

    void SetupMesh();
    void Cleanup();
};

} // namespace Engine
