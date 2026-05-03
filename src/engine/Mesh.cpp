#include "Mesh.h"
#include <iostream>

namespace Engine {

Mesh::Mesh() = default;

Mesh::~Mesh() {
    Cleanup();
}

void Mesh::Cleanup() {
    if (m_EBO != 0) {
        glDeleteBuffers(1, &m_EBO);
        m_EBO = 0;
    }
    if (m_VBO != 0) {
        glDeleteBuffers(1, &m_VBO);
        m_VBO = 0;
    }
    if (m_VAO != 0) {
        glDeleteVertexArrays(1, &m_VAO);
        m_VAO = 0;
    }
    m_IndexCount = 0;
    m_VertexCount = 0;
}

void Mesh::SetVertices(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices) {
    Cleanup();  // Nettoyer l'ancienne mesh
    
    m_VertexCount = static_cast<GLsizei>(vertices.size());
    m_IndexCount = static_cast<GLsizei>(indices.size());
    m_HasIndices = !indices.empty();
    
    // Générer les buffers
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    if (m_HasIndices) {
        glGenBuffers(1, &m_EBO);
    }
    
    // Binding VAO = "enregistrer" la configuration
    glBindVertexArray(m_VAO);
    
    // VBO - données des vertices
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    
    // EBO - indices (si présents)
    if (m_HasIndices) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }
    
    // Configuration des attributs de vertex
    // Position (location = 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    
    // Color (location = 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
    
    // TexCoord (location = 2)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));
    
    // Normal (location = 3)
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    
    // Unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    std::cout << "[OK] Mesh créée: " << m_VertexCount << " vertices, " << m_IndexCount << " indices\n";
}

void Mesh::Bind() const {
    glBindVertexArray(m_VAO);
}

void Mesh::Unbind() const {
    glBindVertexArray(0);
}

void Mesh::Draw() const {
    if (m_HasIndices) {
        glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, m_VertexCount);
    }
}

void Mesh::UpdateVertices(const std::vector<Vertex>& vertices) {
    if (m_VBO == 0) return;
    
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// ==================== PRIMITIVES ====================

Mesh Mesh::CreateTriangle(const glm::vec3& color) {
    Mesh mesh;
    
    // Triangle équilatéral simple
    std::vector<Vertex> vertices = {
        Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), color),  // Bas gauche
        Vertex(glm::vec3( 0.5f, -0.5f, 0.0f), color),  // Bas droite
        Vertex(glm::vec3( 0.0f,  0.5f, 0.0f), color)   // Haut
    };
    
    // Pas d'indices pour un triangle simple
    std::vector<GLuint> indices;
    
    mesh.SetVertices(vertices, indices);
    return mesh;
}

Mesh Mesh::CreateCube(float size) {
    Mesh mesh;
    
    float s = size / 2.0f;  // Demi-taille
    
    // Couleurs différentes pour chaque face
    glm::vec3 red(1.0f, 0.2f, 0.2f);     // Face avant
    glm::vec3 green(0.2f, 1.0f, 0.2f);   // Face arrière
    glm::vec3 blue(0.2f, 0.2f, 1.0f);    // Face haut
    glm::vec3 yellow(1.0f, 1.0f, 0.2f);  // Face bas
    glm::vec3 cyan(0.2f, 1.0f, 1.0f);    // Face droite
    glm::vec3 magenta(1.0f, 0.2f, 1.0f); // Face gauche
    
    // 8 coins du cube
    glm::vec3 p[8] = {
        glm::vec3(-s, -s,  s), // 0: avant-bas-gauche
        glm::vec3( s, -s,  s), // 1: avant-bas-droite
        glm::vec3( s,  s,  s), // 2: avant-haut-droite
        glm::vec3(-s,  s,  s), // 3: avant-haut-gauche
        glm::vec3(-s, -s, -s), // 4: arrière-bas-gauche
        glm::vec3( s, -s, -s), // 5: arrière-bas-droite
        glm::vec3( s,  s, -s), // 6: arrière-haut-droite
        glm::vec3(-s,  s, -s)  // 7: arrière-haut-gauche
    };
    
    std::vector<Vertex> vertices = {
        // Face AVANT (z+) - Rouge
        Vertex(p[0], red), Vertex(p[1], red), Vertex(p[2], red),
        Vertex(p[0], red), Vertex(p[2], red), Vertex(p[3], red),
        
        // Face ARRIÈRE (z-) - Vert
        Vertex(p[5], green), Vertex(p[4], green), Vertex(p[7], green),
        Vertex(p[5], green), Vertex(p[7], green), Vertex(p[6], green),
        
        // Face HAUT (y+) - Bleu
        Vertex(p[3], blue), Vertex(p[2], blue), Vertex(p[6], blue),
        Vertex(p[3], blue), Vertex(p[6], blue), Vertex(p[7], blue),
        
        // Face BAS (y-) - Jaune
        Vertex(p[4], yellow), Vertex(p[5], yellow), Vertex(p[1], yellow),
        Vertex(p[4], yellow), Vertex(p[1], yellow), Vertex(p[0], yellow),
        
        // Face DROITE (x+) - Cyan
        Vertex(p[1], cyan), Vertex(p[5], cyan), Vertex(p[6], cyan),
        Vertex(p[1], cyan), Vertex(p[6], cyan), Vertex(p[2], cyan),
        
        // Face GAUCHE (x-) - Magenta
        Vertex(p[4], magenta), Vertex(p[0], magenta), Vertex(p[3], magenta),
        Vertex(p[4], magenta), Vertex(p[3], magenta), Vertex(p[7], magenta),
    };
    
    // Pas d'indices pour le cube (on pourrait optimiser avec indices mais plus simple sans)
    std::vector<GLuint> indices;
    
    mesh.SetVertices(vertices, indices);
    return mesh;
}

Mesh Mesh::CreateQuad(float size) {
    Mesh mesh;
    
    float s = size / 2.0f;
    glm::vec3 white(1.0f, 1.0f, 1.0f);
    
    std::vector<Vertex> vertices = {
        Vertex(glm::vec3(-s, -s, 0.0f), white, glm::vec2(0.0f, 0.0f), glm::vec3(0, 0, 1)),
        Vertex(glm::vec3( s, -s, 0.0f), white, glm::vec2(1.0f, 0.0f), glm::vec3(0, 0, 1)),
        Vertex(glm::vec3( s,  s, 0.0f), white, glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, 1)),
        Vertex(glm::vec3(-s,  s, 0.0f), white, glm::vec2(0.0f, 1.0f), glm::vec3(0, 0, 1))
    };
    
    std::vector<GLuint> indices = {
        0, 1, 2,
        0, 2, 3
    };
    
    mesh.SetVertices(vertices, indices);
    return mesh;
}

} // namespace Engine
