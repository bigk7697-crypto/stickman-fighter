#include "GameObject.h"
#include <iostream>
#include <algorithm>

namespace Game {

GameObject::GameObject(const std::string& name, ObjectType type)
    : m_Name(name), m_Type(type) {
    // Par défaut, une boîte de collision de taille 1x1x1
    m_LocalAABB = Engine::AABB::FromCenterSize(glm::vec3(0.0f), glm::vec3(1.0f));
}

void GameObject::SetPosition(const glm::vec3& pos) {
    m_Position = pos;
}

void GameObject::SetRotation(float angleDegrees, const glm::vec3& axis) {
    m_RotationAngle = angleDegrees;
    m_RotationAxis = glm::normalize(axis);
}

void GameObject::SetScale(const glm::vec3& scale) {
    m_Scale = scale;
    // Mettre à jour la boîte de collision locale
    m_LocalAABB = Engine::AABB::FromCenterSize(glm::vec3(0.0f), scale);
}

glm::mat4 GameObject::GetModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    
    // Position de base + offset d'animation
    glm::vec3 finalPos = m_Position + m_Animator.GetPositionOffset();
    model = glm::translate(model, finalPos);
    
    // Rotation de base + offset d'animation
    float finalRot = m_RotationAngle + m_Animator.GetRotationOffset();
    if (finalRot != 0.0f) {
        model = glm::rotate(model, glm::radians(finalRot), m_RotationAxis);
    }
    
    // Scale de base + offset d'animation
    glm::vec3 finalScale = m_Scale + m_Animator.GetScaleOffset();
    finalScale = glm::max(finalScale, glm::vec3(0.01f));  // Éviter scale négatif ou nul
    model = glm::scale(model, finalScale);
    
    return model;
}

void GameObject::SetCollisionBox(const glm::vec3& size) {
    m_LocalAABB = Engine::AABB::FromCenterSize(glm::vec3(0.0f), size);
}

Engine::AABB GameObject::GetWorldAABB() const {
    // Transformer l'AABB locale en coordonnées monde
    // Note: Pour une rotation exacte, il faudrait transformer les 8 coins
    // Mais pour une AABB alignée, on prend le min/max transformés
    
    glm::vec3 center = m_Position;
    glm::vec3 halfSize = m_LocalAABB.GetHalfSize();
    
    // Appliquer le scale
    halfSize *= m_Scale;
    
    // Pour une AABB alignée aux axes (pas de rotation), c'est simple:
    return Engine::AABB(center - halfSize, center + halfSize);
}

void GameObject::SetMesh(const Engine::Mesh& mesh) {
    m_Mesh = mesh;
}

void GameObject::SetColor(const glm::vec3& color) {
    m_Color = color;
    m_UseMeshColor = false;
}

void GameObject::Render(Engine::Shader& shader) const {
    if (!m_Mesh.IsValid()) return;
    
    // Envoyer la matrice modèle au shader
    shader.SetMat4("u_Model", GetModelMatrix());
    
    // TODO: Envoyer la couleur si nécessaire (nécessite une uniform dans le shader)
    
    m_Mesh.Bind();
    m_Mesh.Draw();
    m_Mesh.Unbind();
}

bool GameObject::Move(const glm::vec3& delta, const std::vector<GameObject*>& obstacles) {
    if (!m_CollisionEnabled || delta == glm::vec3(0.0f)) {
        m_Position += delta;
        return true;
    }
    
    // Essayer le mouvement complet d'abord
    glm::vec3 newPos = m_Position + delta;
    
    // Sauvegarder l'ancienne position
    glm::vec3 oldPos = m_Position;
    
    // Déplacer temporairement pour tester
    m_Position = newPos;
    Engine::AABB newAABB = GetWorldAABB();
    
    // Vérifier les collisions avec tous les obstacles
    bool collision = false;
    GameObject* collidedWith = nullptr;
    
    for (auto* obstacle : obstacles) {
        if (obstacle == this || !obstacle->IsCollisionEnabled()) continue;
        
        if (newAABB.Intersects(obstacle->GetWorldAABB())) {
            collision = true;
            collidedWith = obstacle;
            break;
        }
    }
    
    if (!collision) {
        // Pas de collision, mouvement accepté
        return true;
    }
    
    // Collision détectée ! Essayer de glisser le long des axes
    // Technique: essayer X seul, puis Z seul, puis les deux
    
    // Reset position
    m_Position = oldPos;
    
    // Essayer X seul
    glm::vec3 moveX(delta.x, 0.0f, 0.0f);
    m_Position = oldPos + moveX;
    bool collidesX = false;
    for (auto* obstacle : obstacles) {
        if (obstacle == this || !obstacle->IsCollisionEnabled()) continue;
        if (GetWorldAABB().Intersects(obstacle->GetWorldAABB())) {
            collidesX = true;
            break;
        }
    }
    
    if (collidesX) {
        m_Position = oldPos;  // Reset X
    }
    
    // Essayer Z seul (depuis la position actuelle qui peut déjà inclure X)
    glm::vec3 moveZ(0.0f, 0.0f, delta.z);
    glm::vec3 posAfterX = m_Position;
    m_Position = m_Position + moveZ;
    bool collidesZ = false;
    for (auto* obstacle : obstacles) {
        if (obstacle == this || !obstacle->IsCollisionEnabled()) continue;
        if (GetWorldAABB().Intersects(obstacle->GetWorldAABB())) {
            collidesZ = true;
            break;
        }
    }
    
    if (collidesZ) {
        m_Position = posAfterX;  // Reset Z
    }
    
    // Appliquer Y toujours (pas de collision verticale pour l'instant - pas de gravité)
    m_Position.y += delta.y;
    
    // Vérifier si on a bougé au moins un peu
    return m_Position != oldPos;
}

void GameObject::PrintInfo() const {
    std::cout << "===== GameObject: " << m_Name << " =====\n";
    std::cout << "Type: " << static_cast<int>(m_Type) << "\n";
    std::cout << "Position: [" << m_Position.x << ", " << m_Position.y << ", " << m_Position.z << "]\n";
    std::cout << "Scale: [" << m_Scale.x << ", " << m_Scale.y << ", " << m_Scale.z << "]\n";
    std::cout << "AABB Center: [" << GetWorldAABB().GetCenter().x << ", " 
              << GetWorldAABB().GetCenter().y << ", " << GetWorldAABB().GetCenter().z << "]\n";
    std::cout << "AABB Size: [" << GetWorldAABB().GetSize().x << ", "
              << GetWorldAABB().GetSize().y << ", " << GetWorldAABB().GetSize().z << "]\n";
    std::cout << "Collision: " << (m_CollisionEnabled ? "ON" : "OFF") << "\n";
    std::cout << "================================\n";
}

} // namespace Game
