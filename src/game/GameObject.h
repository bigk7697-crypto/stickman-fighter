#pragma once
#include "../engine/AABB.h"
#include "../engine/Mesh.h"
#include "Animator.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>

namespace Game {

// Types d'objets de jeu
enum class ObjectType {
    Player,     // Joueur contrôlable
    Obstacle,   // Mur, rocher, etc.
    Enemy,      // Ennemi (à implémenter plus tard)
    Item,       // Objet ramassable (à implémenter)
    Ground      // Sol (pas de collision verticale)
};

class GameObject {
public:
    GameObject(const std::string& name, ObjectType type);
    virtual ~GameObject() = default;
    
    // Position et orientation
    void SetPosition(const glm::vec3& pos);
    void SetRotation(float angleDegrees, const glm::vec3& axis);
    void SetScale(const glm::vec3& scale);
    
    glm::vec3 GetPosition() const { return m_Position; }
    float GetRotationAngle() const { return m_RotationAngle; }
    glm::vec3 GetRotationAxis() const { return m_RotationAxis; }
    glm::vec3 GetScale() const { return m_Scale; }
    
    // Matrice de transformation modèle
    glm::mat4 GetModelMatrix() const;
    
    // Collision
    void SetCollisionBox(const glm::vec3& size);
    void SetCollisionEnabled(bool enabled) { m_CollisionEnabled = enabled; }
    bool IsCollisionEnabled() const { return m_CollisionEnabled; }
    
    Engine::AABB GetWorldAABB() const;  // AABB en coordonnées monde
    Engine::AABB GetLocalAABB() const { return m_LocalAABB; }
    
    // Visuel
    void SetMesh(const Engine::Mesh& mesh);
    void SetColor(const glm::vec3& color);
    void Render(Engine::Shader& shader) const;
    bool HasMesh() const { return m_Mesh.IsValid(); }
    
    // Propriétés
    std::string GetName() const { return m_Name; }
    ObjectType GetType() const { return m_Type; }
    
    // Déplacement avec collision
    // Retourne true si le mouvement a été effectué, false si bloqué
    bool Move(const glm::vec3& delta, const std::vector<GameObject*>& obstacles);
    
    // Pour debug
    void PrintInfo() const;

protected:
    std::string m_Name;
    ObjectType m_Type;
    
    // Transform
    glm::vec3 m_Position = glm::vec3(0.0f);
    float m_RotationAngle = 0.0f;
    glm::vec3 m_RotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_Scale = glm::vec3(1.0f);
    
    // Collision
    Engine::AABB m_LocalAABB;  // AABB en coordonnées locales (centrée sur l'origine)
    bool m_CollisionEnabled = true;
    
    // Visuel
    Engine::Mesh m_Mesh;
    glm::vec3 m_Color = glm::vec3(1.0f, 1.0f, 1.0f);
    bool m_UseMeshColor = true;  // Si false, utilise m_Color
    
    // Animation
    Animator m_Animator;
    
public:
    // Accès à l'animateur
    Animator& GetAnimator() { return m_Animator; }
    void UpdateAnimation(float deltaTime) { m_Animator.Update(deltaTime); }
};

} // namespace Game
